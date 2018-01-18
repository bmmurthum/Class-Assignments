/*

@author - Brendon Murthum
@version - Jan 2018

CIS 452 - Operating Systems
Prof. Dulimarta

Your assignment is to write a simple program that accepts user input without 
echoing what the user types back to the terminal. This would be advisable, for 
example, when asking a user to enter a password or passphrase. In particular, 
your program should:

- Obtain and store the default (current) terminal parameters
- Modify the current terminal behavior to turn off terminal echo
- Input a word or phrase (i.e. the password/passphrase)
- Output whatever the user entered
- Restore default terminal behavior

Code was written with light reference to IBM's support pages of the "termios"
library. This can be found at the following link.

https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0
/com.ibm.zos.v2r3.bpxbd00/rttcga.htm#rttcga

*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

int main (int argc, char **argv) {

    /* User's cleartext username. */
    char username[30];
    /* User's "hidden" username entry. */
    char password[20];
    /* User's cleartext email entry. */
    char email[30];
    /* The terminal struct for changing parameters. */
    struct termios term;
    /* Boolean that holds TRUE if we changed the setting, FALSE if the same. */
    bool echo_changed;

    /* Obtain and store terminal parameters. */
    if (tcgetattr(STDIN_FILENO, &term) != 0)
        perror("tcgetattr() error");
        
    /* Display intro text. */
    printf("\n");
    printf("The following is a display of changing terminal-settings.");
    printf("\n");
    printf("\n");

    /* Show example of the default behavior. */
    printf("Enter Username: ");
    scanf("%s", username);
    printf("\n");

    /* Modify current terminal behavior. */
    
    /* Flips the ECHO setting, if it was originally TRUE. */
    if (term.c_lflag & ECHO) {
        printf("  ECHO is originally turned on. Turning off ECHO... \n");
        printf("\n");
        echo_changed = true;
        term.c_lflag = term.c_lflag ^ ECHO;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
            perror("tcsetattr() error");
    }        
    else {
        printf("ECHO was not originally set.\n");
        echo_changed = false;
    }

    /* Input "User-Password." */
    printf("Enter Password: ");
    scanf("%s", password);
    printf("\n");
    printf("\n");
    
    /* Restore default terminal behaviors. */
    if (echo_changed) {
        term.c_lflag = term.c_lflag ^ ECHO;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
            perror("tcsetattr() error");
        else
            printf("  Resetting ECHO to default..\n");
        printf("\n");
    }
    
    /* Showing entry with ECHO back on. */
    printf("Enter Email Address: ");
    scanf("%s", email);
    printf("\n");
    
    /* Output what the user entered. */
    printf("Showing entered values: \n");
    printf("Username: %s \n", username);
    printf("Password: %s \n", password);
    printf("Email: %s \n", email);
    printf("\n");
    
    return 0;
}


