#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>


void printHeader()
{
    char *header =
        "digraph finite_state_machine {\n"
        "	rankdir=LR;\n"
        "	size=\"40,10\"\n"
        "	node [shape = circle];\n";

    printf("%s", header);
    return;
}

void printTrailer()
{
    printf("}\n\n");
    return;
}
int main(int argc, char ** argv)
{
    char   line[256];
    char   oldState[128];
    char   newState[128];
    FILE * fp;
    int filebytes;
    int retval = 0;
    int lineNumber;
    int scopeCount;
    int ii;
    int header;
    char *progname;
    char *statevariable;
    char *filename;
    char *parse1, *parse2, *parse3;

    progname = "fsm2dot";
    filename = NULL;
    filebytes = -1;
    header = 0;

    /****************************************************************************/
    /* Process Command Line.                                                    */
    /****************************************************************************/
    if(argc != 3)
    {
        fprintf(stderr, "Usage: fsm2dot <state_variable> <sourcefile.c>\n");
    }
    else
    {
        statevariable = argv[1];
        filename = argv[2];
    }

    /****************************************************************************/
    /* Open the file and determine its size.                                    */
    /****************************************************************************/
    if(filename)
    {
        if((fp = fopen(filename, "r")) == NULL)
        {
            perror(filename);
        }
        else
        {
            if((filebytes=fseek(fp, 0, SEEK_END)) == -1)
            {
                perror("seek()");
                filebytes = -1;
            }
            else
            {
                filebytes = ftell(fp);
                rewind(fp);
            }

            if(filebytes <= 0)
            {
                fclose(fp);
                filename = NULL;
            }
        }
    }

    /****************************************************************************/
    /* Exit if invalid inputs are detected.                                     */
    /****************************************************************************/
    if(filebytes <= 0)
    {
        fprintf(stderr, "%s: Could not process file.\n", progname);
        exit(-1);
    }

    fprintf(stderr, "File size is %d bytes.\n", filebytes);
    strcpy(oldState, "unassigned");

    /****************************************************************************/
    /* Find the state machine.                                                  */
    /****************************************************************************/
    lineNumber = 0;
    scopeCount = 0;
    do
    {
        if(fgets(line, sizeof(line), fp) == NULL)
        {
            fprintf(stderr, "%s: State Machine switch() not found.\n", progname);
            lineNumber = 0;
        }
        lineNumber++;

    } while((strstr(line, "switch") == NULL) || (strstr(line, statevariable) == NULL));

    /****************************************************************************/
    /* Process each line of the state machine.                                  */
    /* State transition outputs look like this:                                 */
    /*    OldState -> NewState [ label = "Reason" ];                            */
    /****************************************************************************/
    if(lineNumber > 0)
    {
        fprintf(stderr, "state machine found at line %d\n", lineNumber);

        // Count curly braces to stay in the scope of the state machine.
        for(ii=0;ii<strlen(line);ii++)
        {
            if(line[ii] == '{') scopeCount++;
            if(line[ii] == '}') scopeCount--;
        }

        do
        {
            if(fgets(line, sizeof(line), fp) == NULL)
            {
                fprintf(stderr, "%s: Error reading state machine on line %d.\n", progname, lineNumber);
                lineNumber = 0;
                break;
            }
            lineNumber++;

            // Count curly braces to stay in the scope of the state machine.
            for(ii=0;ii<strlen(line);ii++)
            {
                if(line[ii] == '{') scopeCount++;
                if(line[ii] == '}') scopeCount--;
            }

            // Each 'case' inside the switch on the FSM state variable is the 'OldState'.
            if(((parse1=strstr(line, "case")) != NULL) && ((parse2=strstr(parse1, ":")) != NULL))
            {
                parse1 += strlen("case ");
                *parse2 = '\0';
                parse3 = &oldState[0];
                for(ii=0;ii<strlen(parse1);ii++)
                {
                    if(isalnum(parse1[ii]))
                    {
                        *parse3++ = parse1[ii];
                    }
                }
                *parse3 = '\0';

//                printf("State: %s\n", state);
            }

            // Each statevariable assignment inside the switch on the FSM state variable is a 'NewState'.
            if((parse1=strstr(line, statevariable)) != NULL)
            {
                if(((parse2=strstr(parse1, "=")) != NULL) && ((strstr(parse1, "==")) == NULL))
                {
 //                   printf("Assignment: %s\n", parse2);

                    parse2++;                           // skip the '='
                    if((parse3 = strstr(parse2, ";")) != NULL)
                    {
                        *parse3 = '\0';
                    }
                    else
                    {
                        fprintf(stderr, "%s: Parse error line %d\n", progname, lineNumber);
                        scopeCount = 0;
                        lineNumber = 0;
                        break;
                    }

                    parse3 = &newState[0];
                    for(ii=0;ii<strlen(parse2);ii++)
                    {
                        if(isalnum(parse2[ii]))
                        {
                            *parse3++ = parse2[ii];
                        }
                    }
                    *parse3 = '\0';

                    if(header == 0)
                    {
                        printHeader();
                        header = 1;
                    }

                    printf("    %s -> %s [ label =\"\" ];\n", oldState, newState);
                }
            }

        } while(scopeCount > 0);

        if(lineNumber > 0)
        {
            printTrailer();
        }
    }

    fclose(fp);
    return retval;
}

