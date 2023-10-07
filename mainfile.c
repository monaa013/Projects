#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define a structure to store user information
struct User {
    char username[100];
    char password[100];
};

// Define a structure to store train details
struct Train {
    int trainId;
    char trainName[100];
    char source[100];
    char destination[100];
    char startTime[100];
    char endTime[100];
};

// Define a structure to store seat booking information
struct SeatBooking {
    int trainId;
    int seatNumber;
    char passengerName[100];
};

// Function to register a new user
void registerUser() {
    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    FILE *userFile = fopen("users.txt", "a");
    if (userFile != NULL) {
        fprintf(userFile, "%s %s\n", newUser.username, newUser.password);
        fclose(userFile);
        printf("Registration successful! You can now log in.\n");
    } else {
        printf("Error registering user.\n");
    }
}

// Function to check if a user exists
int userExists(char *username, char *password) {
    struct User user;
    FILE *userFile = fopen("users.txt", "r");
    if (userFile != NULL) {
        while (fscanf(userFile, "%s %s\n", user.username, user.password) != EOF) {
            if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
                fclose(userFile);
                return 1; // User found
            }
        }
        fclose(userFile);
    }
    return 0; // User not found
}

// Function to display train details from a file
void displayTrainDetails() {
    int chosetrainID;
    printf("Enter the train id: ");
    scanf("%d", &chosetrainID);
    FILE *trainFile = fopen("predefined_trains.txt", "r");
    if (trainFile != NULL) {
        struct Train train;
        int found = 0;
        printf("Train Details:\n");
        while (fscanf(trainFile, "%d,%[^,],%[^,],%[^,],%[^,],%[^\n]\n", &train.trainId, train.trainName, train.source, train.destination, train.startTime, train.endTime) != EOF) {
            if (train.trainId == chosetrainID) {
                printf("Train ID: %d\n", train.trainId);
                printf("Train Name: %s\n", train.trainName);
                printf("Source: %s\n", train.source);
                printf("Destination: %s\n", train.destination);
                printf("Starting Time: %s\n", train.startTime);
                printf("Ending Time: %s\n", train.endTime);
                printf("\n");
                found = 1;
                break;
            }
        }
        fclose(trainFile);

        if (!found) {
            printf("Train with ID %d not found.\n", chosetrainID);
        }
    } else {
        printf("Error opening predefined file for reading\n");
    }
}

// Function to book a seat
void bookSeat() {
    int selectedTrainId;
    printf("Enter the Train ID you want to book a seat for: ");
    scanf("%d", &selectedTrainId);

    // You can modify this to load available seats and their status from a file or database
    int availableSeats = 50; // Example: 50 available seats for all trains

    printf("Available Seats: %d\n", availableSeats);

    if (availableSeats <= 0) {
        printf("No seats available for booking.\n");
        return;
    }

    struct SeatBooking booking;
    booking.trainId = selectedTrainId;

    printf("Enter your name: ");
    scanf("%s", booking.passengerName);

    printf("Enter the seat number you want to book (1 to %d): ", availableSeats);
    scanf("%d", &booking.seatNumber);

    if (booking.seatNumber < 1 || booking.seatNumber > availableSeats) {
        printf("Invalid seat number. Please choose a valid seat.\n");
        return;
    }

    // You can add logic here to check seat availability and update the seat status

    // For this example, simply decrement availableSeats to simulate booking
    availableSeats--;

    printf("Seat booked successfully!\n");
    printf("Passenger Name: %s\n", booking.passengerName);
    printf("Train ID: %d\n", booking.trainId);
    printf("Seat Number: %d\n", booking.seatNumber);
     FILE *ticketFile = fopen("ticket_details.txt", "a");
    if (ticketFile != NULL) {
        fprintf(ticketFile, "Passenger Name: %s\n", booking.passengerName);
        fprintf(ticketFile, "Train ID: %d\n", booking.trainId);
        fprintf(ticketFile, "Seat Number: %d\n", booking.seatNumber);
        fprintf(ticketFile, "----------------------------------------\n");
        fclose(ticketFile);
        printf("Ticket details saved to file.\n");
    } else {
        printf("Error saving ticket details.\n");
    }

    // Return to the main menu
}


   // Function to view booked seat details
void viewBookedSeats() {
    FILE *ticketFile = fopen("ticket_details.txt", "r");
    if (ticketFile != NULL) {
        char line[100];
        printf("Booked Seat Details:\n");
        while (fgets(line, sizeof(line), ticketFile) != NULL) {
            printf("%s", line);
        }
        fclose(ticketFile);
    } else {
        printf("No booked seat details found.\n");
    }
}

int main() {
    int choice1;
    int choice2;
    char username[100];
    char password[100];

    printf("Welcome to the Train Reservation System!\n");

    for (int i = 3; i <=3; i--)
    {
        printf("1. Register\n");
        printf("2. Login\n");
        scanf("%d", &choice1);

        if (choice1 == 1) {
            registerUser();
        } else if (choice1 == 2) {
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);

            if (userExists(username, password)) {
                printf("Login successful!\n");
                break;
            } else {
                printf("Login failed.You have %d tries ! Please try again.\n", i--);
            }
            
        } else {
            printf("Invalid choice. Please try again.\n");
            
        }
    }
 
   // Continue registration and login until choice 2 (Login)

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display Train Details\n");
        printf("2. Book a Seat\n");
        printf("3. View Booked Seats\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);

        switch (choice2) {
            case 1:
                displayTrainDetails();
                break;
            case 2:
                bookSeat();
                break;
            case 3:
                printf("-------------------------");
                viewBookedSeats();
                break;
            case 4:
                printf("Thank you for using the Train Reservation System!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}