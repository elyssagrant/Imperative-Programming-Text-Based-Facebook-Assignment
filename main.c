/********* main.c ********
    Student Name 	= Elyssa Grant
    Student Number	= 101258660
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

     // Your solution goes here

    //declaring variables
    unsigned short int menu_choice; //holds onto the user's decision from the main menu
    char new_username[USERNAME_LEN]; //holds new usernames to be inputted
    char username_in[USERNAME_LEN]; //holds username choices for menus
    char new_password[PASSWORD_LEN]; //holds new passwords for new users
    unsigned short int number_input; //holds numerical values, mostly for sub-menus
    user_t * user_location; //holds the location of a specific user
    char new_post[POST_LEN]; //holds the message the user wants to input into a new post
    unsigned short int posts_delete; //holds the value of the post the user wants to delete
    _Bool deletion_success; //holds whether the friend was deleted successfully or not

    //printing opening lines
    printf("***********************************************\n");
    printf("\tWelcome to Text-Based Facebook\n");
    printf("***********************************************\n");
    printf("\n");

    //looping until the user wants to quit the program
    while(menu_choice != QUIT)
    {
        //looping until the user enters a proper number
        do
        {
            //calling the main menu
            print_menu();

            printf("Enter your choice: ");
            //taking in user choice 
            scanf("%d", &menu_choice);

            if(menu_choice < COUNT_START || menu_choice > QUIT)
            {
                //notifying the user that their choice is invalid
                printf("Invalid choice. Please try again.\n\n");
            }
        }while(menu_choice < COUNT_START || menu_choice > QUIT);
        

        //determining where the user wants to go based on their input
        if(menu_choice == ADD_USER)
        {
            //asking for username and password to send to the add_user fxn
            printf("Enter a username: ");
            scanf("%s", &new_username);
            printf("Enter an up to 15 characters password: ");
            scanf("%s", &new_password);

            //calling the add_user function to add the user into the database
            users = add_user(users, new_username, new_password);

            printf("\n **** User Added! ****\n\n");
        }
        else if(menu_choice == UPDATE)
        {
           //asking the user for the username they would like to update the password for
           printf("Enter username to update their password: ");
           scanf("%s", username_in);
           printf("\n");

           //finding the user in the database
           user_location = find_user(users, username_in);

           if(user_location != NULL)
           {
                printf("Enter a new password that is up to 15 characters: ");
                scanf("%s", new_password);

                //updating the password
                strcpy(user_location->password, new_password);

                printf("\n**** Password changed! ****\n\n");
           }
        }
        else if(menu_choice == MANAGE_POSTS)
        {
            //Asking for the user whose posts should be managed
            printf("\nEnter username to manage their posts: ");
            scanf(" %s", username_in);
            //finding the user
            user_location = find_user(users, username_in);

            //if the user was found
            if(user_location != NULL)
            {
                //looping until the user wants to quit the posts submenu
                do
                {
                    //calling the post display function, which will take a username and display that username's posts
                    display_user_posts(user_location);

                    //looping until user enters a correct value
                    do
                    {
                        //Printing menu for the posts
                        printf("\n1. Add a new user post\n");
                        printf("2. Remove a users post\n");
                        printf("3. Return to main menu\n");
                        printf("\nYour choice: ");

                        //getting user to decide between the post options
                        scanf(" %d", &number_input);
                        if(number_input < COUNT_START || number_input > POST_RETURN)
                        {
                            printf("Invalid choice. Please try again\n");
                        }
                    }while(number_input <COUNT_START || number_input > POST_RETURN);

                    //going into the posts sub-menu
                    if(number_input == 1)
                    {
                        //getting user input for the postc
                        printf("Enter your post content: ");
                        scanf(" %[^\n]s", new_post);
                        //calling the add post function
                        add_post(user_location, new_post);

                        printf("Post added to your profile\n");
                    }
                    else if(number_input == TWO)
                    {
                        //getting user input
                        printf("Which post do you want to delete? ");
                        scanf("%d", &posts_delete);
                        //calling the delete post function
                        deletion_success = delete_post(user_location, posts_delete);

                        //if there was an error, returning to main menu
                        if(!deletion_success)
                        {
                            printf("Invalid post's number\n\n");
                        }
                    }
                //user choice = 3 will cause the program to return to the main menu
                } while (number_input != POST_RETURN);
            }

            //clearing the number input so it can be used later
            number_input = RESET;
        }
        else if(menu_choice == FRIENDS)
        {
            //Asking for the user whose posts should be managed
            printf("Enter username to manage their friends: ");
            scanf(" %s", username_in);
            //finding the user
            user_location = find_user(users, username_in);

            if(user_location != NULL)
            {
                //looping until user wants to quit
                do
                {
                    //looping until the user enters a valid input
                    do
                    {
                        //menu header
                        printf("-----------------------------------------\n");
                        printf("\t\t %s's friends\n", username_in);
                        printf("-----------------------------------------\n\n");
                        //printing menu
                        printf("1. Display all user's friends\n");
                        printf("2. Add a new friend\n");
                        printf("3. Delete a friend\n");
                        printf("4. Return to main menu\n");

                        printf("\n Your choice: ");
                        scanf("%d", &number_input);

                        if(number_input < COUNT_START || number_input > FRIEND_RETURN)
                        {
                            printf("Invalid choice. Please try again\n");
                        }
                    }while(number_input < COUNT_START || number_input > FRIEND_RETURN);

                    printf("\n");

                    //Determining what to do based on the user's input
                    if(number_input == ONE)
                    {
                        //calling the function to display user friends
                        display_user_friends(user_location);
                    }
                    else if(number_input  == TWO)
                    {
                        //getting the new friend's name
                        printf("Enter a new friends' name: ");
                        scanf(" %s", new_username);

                        //calling the add_friend fxn
                        add_friend(user_location, new_username);

                        printf("Friend added to the list\n\n");
                    }
                    else if(number_input == THREE)
                    {
                        //displaying the user's friends
                        display_user_friends(user_location);

                        //getting the friend the user wants to delete
                        printf("Enter a friend's name to delete: ");
                        scanf(" %s", username_in);
                        
                        //Attempting to remove the friend
                        deletion_success = delete_friend(user_location, username_in);

                        if(!deletion_success)
                        {
                            //informing the user the friend they entered was invalid
                            printf("Invalid friend's name\n\n");
                        }

                        //displaying the user's updated friend list
                        display_user_friends(user_location);
                    }
                } while (number_input != FRIEND_RETURN);
            }

            //clearing the number_input so it can be used in other sub-menus
            number_input = RESET;
        }
        else if(menu_choice == ALL_POSTS)
        {
            //calling the display all posts function
            display_all_posts(users);
        }
        else if(menu_choice == QUIT)
        {
            //printing the exiting messages
            printf("***********************************************\n");
            printf("Thank you for using Text-Based Facebook\n");
            printf("\t\tGoodbye!\n");
            printf("***********************************************\n");

            //tearing down all memory
            teardown(users);
        }
    }
}