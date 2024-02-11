/********* definitions.c ********
    Student Name 	= Elyssa Grant
    Student Number	= 101258660
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   //creating a new user node
   user_t * new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);

   //adding values to the node
   strcpy(new_user->username, username);
   strcpy(new_user->password, password);
   new_user->next = NULL;
   new_user->friends = NULL;
   new_user->posts = NULL;

   //Case 1: list is empty
   if(users == NULL)
   {
      users = new_user;
   }
   else
   {
      //looping across the list
      for(user_t * wlk = users; wlk != NULL; wlk = wlk->next)
      {
         //Case 2: Node needs to be added right at the head
         if(strcmp(wlk->username, username) > ZERO)
         {
            new_user->next = wlk;
            users = new_user;
            wlk = new_user;
            break;
         }
         //Case 3: Reached end of the list and need to insert at the very end
         if(wlk->next == NULL)
         {
            wlk->next = new_user;
            break;
         }
         //Case 4: Nodes added in middle or end of list
         if(strcmp(wlk->next->username, new_user->username) > ZERO)
         {
            new_user->next = wlk->next;
            wlk->next = new_user;
            break;
         }

      }
   }
   
    return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   //loops across the database
   for(user_t * wlk = users; wlk != NULL; wlk = wlk->next)
   {
      //comparing the username given with the current user
      if(strcmp(wlk->username, username) == ZERO)
      {
         //if found, return a pointer to that user
         return wlk;
      }
   }
   //not found, inform the user and return NULL
   printf("----------------------------------------\n");
   printf("\t\tUser not found.\n");
   printf("-----------------------------------------\n");
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   //only creating the friend node, not checking or anything

   //allocating memory for the new node
   friend_t * new_friend = malloc(sizeof(friend_t));
   assert(new_friend != NULL);

   //initializing the values for the friend
   strcpy(new_friend->username, username);
   new_friend->next = NULL;
    
   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   //if the user inputted is not actually there
   if(user == NULL)
   {
      return;
   }

    //creating a new node for the friend
   friend_t * new_friend = create_friend(friend);
   

   //Case 1: Friends list is empty
   if(user->friends == NULL)
   {
      user->friends = new_friend;
   }
   else
   {
      //looping across the friends list
      for(friend_t * wlk = user->friends; wlk!= NULL; wlk = wlk->next)
      {
         //Case 2: Need to add directly at the head of the list
         if(strcmp(wlk->username, new_friend->username) > ZERO)
         {
            //updating the head
            new_friend->next = user->friends;
            user->friends = new_friend;
            break;
         }
         //Case 3: Need to add at the very end of the list
         else if(wlk->next == NULL)
         {
            wlk->next = new_friend;
            break;
         }
         //Case 4: Add somewhere in the middle
         else if(strcmp(wlk->next->username, new_friend->username) > ZERO)
         {
            new_friend->next = wlk->next;
            wlk->next = new_friend;
            break;
         }
      }
   }

   return;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   //ensuring the person the user inputted is valid
   if(user == NULL)
   {
      return FALSE;
   }

   //declaring variables
   friend_t * to_free; //Holds the friend that we want to delete's memory location

   //Special Case 1: Friend to be removed is very first in the list
   if(strcmp(user->friends->username, friend_name) == ZERO)
   {
      //storing the memory location
      to_free = user->friends;

      //updating the head
      user->friends = user->friends->next;

      //freeing the memory
      free(to_free);
      to_free = NULL;
      return TRUTH;
   }

   //looping across the list to find the friend
   for(friend_t * wlk = user->friends; wlk->next != NULL; wlk = wlk->next)
   {
      //if we found the user, hold onto them and remove from the list
      if(strcmp(wlk->next->username, friend_name) == ZERO)
      {
         to_free = wlk;
         //removing from the list
         wlk->next = wlk->next->next;

         //freeing the memory
         free(to_free);
         to_free = NULL;
         
         return TRUTH;
      }
   }
   
   //if did not find the friend, return 0 (failed)
    return FALSE;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   //allocating memory for the new node
   post_t * new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);
   
   //filling in the content of the post
   strcpy(new_post->content, text);
   new_post->next = NULL;
    
    return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   //Creating a new node for the post
   post_t * new_post = create_post(text);

   //Case 1: There are no posts in the user's profile
   if(user->posts == NULL)
   {
      user->posts = new_post;
   }
   //Case 2: There are other posts in the user's profile
   else 
   {
      //adding the new post at the head of the list
      new_post->next = user->posts;
      user->posts = new_post;
   }

   return;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   //Case 1: There are no posts to delete
   if(user->posts == NULL)
   {

      return FALSE;
   }

   //declaring variables
   unsigned int counter = ZERO;
   post_t * to_delete = NULL;

   //Case 2: Very first post needs to be deleted
   if(number == COUNT_START)
   {
      //holding onto the memory location
      to_delete = user->posts;

      //removing the node from the list
      user->posts = user->posts->next;

      //freeing memory
      free(to_delete);
      to_delete = NULL;

      printf("Post %d was deleted successfully!\n", number);

      return TRUTH;
   }
   //Case 3: Post is in the middle or end of list
   else
   {
      //looping through the list of posts
      for(post_t * curr = user->posts; curr->next != NULL; curr = curr->next)
      {
         //incrementing the counter by 1
         counter++;

         //checking if the next post is the post we want to delete
         if(counter+ONE == number)
         {
            //saving the memory address
            to_delete = curr->next;

            //removing the post from the list
            curr->next = curr->next->next;

            //freeing memory
            free(to_delete);
            to_delete = NULL;

            //informing the user of the success
            printf("Post %d was deleted successfully!\n", number);

            return TRUTH;
         }
      }
   }

   //if we didn't find the post, returning false
   return FALSE;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   //Top formatting
   printf("----------------------------------------\n");
   printf("\t%s's posts\n", user->username);

   //Informing the user if there are no posts
   if(user->posts == NULL)
   {
      printf("No posts available for %s\n", user->username);
   }
   else
   {
      //declaring variables
      unsigned short int counter = COUNT_START; //Holds the number to display beside the post

      //looping across the user's posts
      for(post_t * post = user->posts; post != NULL; post = post->next)
      {
         //Displaying the post
         printf("%d- %s: %s\n", counter, user->username, post);

         //increasing the counter by 1
         counter ++;
      }
   }

   //Bottom formatting
   printf("----------------------------------------\n");

   return;
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   //Opening dialogue
   printf("\nList of %s's friends:\n", user->username);
   //Informing the user if the friends' list is empty
   if(user->friends == NULL)
   {
      printf("No friends available for %s\n\n", user->username);
      return;
   }
   
   //declaring variables
   unsigned short int counter = COUNT_START; //Increasing number to go beside friend names when displaying them

   //looping across the list of user's friends if present
   for(friend_t * curr_friend = user->friends; curr_friend != NULL; curr_friend = curr_friend->next)
   {
      //printing the current friend
      printf("%d- %s\n",counter, curr_friend->username);

      //increasing the counter by 1
      counter ++;
   }
   //creating whitespace at the end to separate the fxn's output from the rest of the program
   printf("\n");

   return;
}

/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   //declaring local variables
   user_t * cur_user = users; //temporary variable to walk across the users list
   char user_in = '\0'; //holds user input
   unsigned short int counter = COUNT_START; //holds the counter for the number seen beside each post
   _Bool seen_all_posts = FALSE; //Holds whether the user has seen all the posts available, and if so, helps safely exit the program
   //looping until the user wants to stop seeing posts or there are no more posts to be seen
   while(user_in != 'n' && user_in != 'N' && cur_user != NULL && !seen_all_posts)
   {
      //looping over the first two users
      for(unsigned short int i = ZERO; i < TWO; i++)
      {
            //looping across the user's posts
            for(post_t * curr_post = cur_user->posts; curr_post != NULL; curr_post = curr_post->next)
            {
               //for each post, displaying it
               printf("%d- %s: %s\n", counter, cur_user->username, curr_post);

               //incrementing the counter by 1
               counter++;
            }

            //Once finished displaying the user's posts, resetting the counter for the next user
            counter = COUNT_START;

            //going to the next user in the list if it is safe to do so
            if(cur_user->next != NULL)
            {
               cur_user = cur_user->next;
            }
            //If there are no more accounts (and hence no more posts), safely exiting the loop
            else
            {
               seen_all_posts = TRUTH;
               break;
            }
      }
      do
      {
         //asking user if they want to see the posts made by the next two users
         printf("\n\nDo you want to display the next 2 users posts? (Y/N): ");
         scanf(" %c",&user_in);

         //ensuring the user entered a proper value
         if(user_in != 'y' && user_in != 'Y' && user_in != 'n' && user_in != 'N')
         {
            printf("Unknown input\n");
         }
      }while(user_in != 'y' && user_in != 'Y' && user_in != 'n' && user_in != 'N');
      
      printf("\n\n");
   }

   //Letting the user know if they have seen all the posts before exiting the program
   if(seen_all_posts)
   {
      printf("\nAll posts have been viewed. Cannot load any more posts\n\n");
   }

   return;
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   //declaring variables
   friend_t * to_delete; //Stores the current friend that needs to be deleted
   post_t * del_post; //stores the current post that needs to be deleted
   user_t * del_user; //stores the current user that will be deleted

    //loop across the user database
    while(users != NULL)
    {
      //for each user:
      //loop across the friends list
      while(users->friends != NULL)
      {
         //store the current node
         to_delete = users->friends;

         //update the head
         users->friends = users->friends->next;

         //remove the friend
         free(to_delete);
         to_delete = NULL;
      }
         
      //loop across the posts list
      while(users->posts != NULL)
      {
         //store the current node
         del_post = users->posts;
         //update the head
         users->posts = users->posts->next;

         //remove each post
         free(del_post);
         del_post = NULL;
      }

      //save the user's location
      del_user = users;
      //update the head
      users = users->next;
      //remove the user
      free(del_user);
      del_user = NULL;
    }
    

}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   //print calls
   printf("***********************************************\n");
   printf("\t\tMAIN MENU:\t\t\n");
   printf("***********************************************\n");
   printf("1. Register a new User\n");
   printf("2. Manage a user's profile (change password)\n");
   printf("3. Manage a user's posts (display/add/remove)\n");
   printf("4. Manage a user's friends (display/add/remove)\n");
   printf("5. Display All Posts\n");
   printf("6. Exit\n\n");

}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
