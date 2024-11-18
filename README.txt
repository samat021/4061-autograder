CSCI 4061 Project #1

Group ID: P1 Group 28

Members:
    Luke Ishag (ishag003)
        Contributions:
            main() primary contributor
            bug fixes
            office hours
            attended group meetings for coding
    Edil Samatar (samat021)
        Contributions:
            print_status() primary contributor
            main() secondary contributor
            office hours
            attended group meetings for coding
    Isaac Sharma (sharm816)
        Contributions:
            main() secondary contributor
            error detection and finding bug sources
            office hours
            attended group meetings for coding
            README.txt
    All members were consistenly constructively communicative with one another both online and in person.

Compiling and Running
    The compiling for autograder.c should not be any more complicated than normal for other submissions of the project.
    To compile:
        With Makefile
            - Unzip submission folder and enter folder directory in terminal
            - Enter "make" in terminal
            - Enter "./autograder <b> <p1> <p2> ... <pn>" in terminal
                - <b> is batch size, <p1> through <pn> are n number of parameters
                - Terminal should begin outputting similar to "Program: p_sol, PID: 819766, Mode: 3 - Triggering a segmentation fault"
                    - Completed when autograder.out has been generated and populated
        Without Makefile
            - All previous steps the same except for step 2
                - Instead, enter "gcc -Wall -g -Wno-unused-variable -o autograder autograder.c"
                    - Same inputs as Makefile method, just entered manually

Assumptions
    - It is assumed that all necessary files outside the submission zip for testing and grading will be provided.
    - It is assumed that correct output during the testing of autograder.c will have similar results as in the grading environment.
        - All work was done for this lab in VOLE or SSH, and so there should not be a difference.
        - It is assumed that slight changes to variable names in the pseudocode will not cause errors in the grading environment.