#include <stdio.h>
#include <string.h>

#define MAX_QUEUE 5
#define MAX_BOOKINGS 10

// Structure for booking details
struct Booking {
    int booking_id;
    char movie_name[30];
    char audience_names[10][20];
    int audience_count;
    int date;
    int time_choice;
    float total_amount;
};

// Global variables
struct Booking bookings[MAX_BOOKINGS];
int booking_count = 0;

int queue[MAX_QUEUE];
int front = -1, rear = -1;

// Function declarations
void enqueue(int booking_id);
void dequeue();
void displayQueue();
void bookTicket();
void viewBookings();
void cancelBooking();
void processBooking();

void enqueue(int booking_id) {
    if (rear == MAX_QUEUE - 1) {
        printf("\n⚠️ Queue is FULL! Please wait for next show.\n");
        return;
    }
    if (front == -1) front = 0;
    rear++;
    queue[rear] = booking_id;
    printf("\n✅ Booking ID %d successfully added to queue!\n", booking_id);
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("\n⚠️ No pending bookings to process.\n");
        return;
    }
    printf("\n✅ Booking ID %d processed and removed from queue.\n", queue[front]);
    front++;
}

void displayQueue() {
    if (front == -1 || front > rear) {
        printf("\n📋 Queue is empty.\n");
        return;
    }
    printf("\n-----------------------------\n");
    printf("|   CURRENT BOOKING QUEUE   |\n");
    printf("-----------------------------\n");
    for (int i = front; i <= rear; i++)
        printf("| Booking ID: %-10d |\n", queue[i]);
    printf("-----------------------------\n");
}

void viewBookings() {
    if (booking_count == 0) {
        printf("\n📋 No bookings yet!\n");
        return;
    }
    printf("\n==============================\n");
    printf("       🎟️ ALL BOOKINGS LIST     \n");
    printf("==============================\n");
    for (int i = 0; i < booking_count; i++) {
        printf("\nBooking ID   : %d\n", bookings[i].booking_id);
        printf("Movie Name   : %s\n", bookings[i].movie_name);
        printf("Audience(s)  : %d\n", bookings[i].audience_count);
        printf("Date         : %d-10-2025\n", bookings[i].date);
        printf("Total Amount : Rs. %.2f\n", bookings[i].total_amount);
    }
    printf("==============================\n");
}

void cancelBooking() {
    if (booking_count == 0) {
        printf("\n❌ No bookings to cancel.\n");
        return;
    }
    int id, found = 0;
    printf("\nEnter Booking ID to cancel: ");
    scanf("%d", &id);
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].booking_id == id) {
            found = 1;
            for (int j = i; j < booking_count - 1; j++)
                bookings[j] = bookings[j + 1];
            booking_count--;
            printf("\n✅ Booking ID %d cancelled successfully!\n", id);
            break;
        }
    }
    if (!found) printf("\n❌ Booking ID not found!\n");
}

void bookTicket() {
    int movie_id, time_choice, date, n, i;
    float total_amount;
    char movies[3][30] = {"Spiderman", "Made In India", "3 Idiots"};
    char names[10][20];
    int booking_id = 1000 + booking_count + 1;

    printf("\nAvailable Movies:\n");
    printf("---------------------------------\n");
    printf("|  1 | Spiderman               |\n");
    printf("|  2 | Made In India           |\n");
    printf("|  3 | 3 Idiots                |\n");
    printf("---------------------------------\n");
    printf("Enter movie ID (1-3): ");
    scanf("%d", &movie_id);
    if (movie_id < 1 || movie_id > 3) {
        printf("\n❌ Invalid Movie Selection!\n");
        return;
    }

    printf("\nEnter number of audience (max 10): ");
    scanf("%d", &n);
    if (n < 1 || n > 10) {
        printf("\n❌ Invalid Audience Count!\n");
        return;
    }

    printf("\nEnter audience names:\n");
    for (i = 0; i < n; i++) {
        printf("Name %d: ", i + 1);
        scanf("%s", names[i]);
    }

    printf("\nEnter date (e.g., 15 for 15th Oct): ");
    scanf("%d", &date);

    printf("\nChoose show time:\n");
    printf("----------------------\n");
    printf("| 1 | 10:30 AM        |\n");
    printf("| 2 | 1:30 PM         |\n");
    printf("| 3 | 3:30 PM         |\n");
    printf("| 4 | 7:00 PM         |\n");
    printf("----------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &time_choice);

    total_amount = n * 350.0;

    struct Booking newBooking;
    newBooking.booking_id = booking_id;
    strcpy(newBooking.movie_name, movies[movie_id - 1]);
    newBooking.audience_count = n;
    newBooking.date = date;
    newBooking.time_choice = time_choice;
    newBooking.total_amount = total_amount;
    for (i = 0; i < n; i++)
        strcpy(newBooking.audience_names[i], names[i]);

    bookings[booking_count++] = newBooking;

    printf("\n✅ Booking successful! Your Booking ID is %d\n", booking_id);
    enqueue(booking_id);
}

int main() {
    int choice;

    printf("****************************************************\n");
    printf("      🎬 MOVIE TICKET BOOKING SYSTEM 🎟️             \n");
    printf("****************************************************\n");

    while (1) {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Book Ticket\n");
        printf("2. View All Bookings\n");
        printf("3. Cancel Booking\n");
        printf("4. View Queue\n");
        printf("5. Process (Dequeue) Booking\n");
        printf("6. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: viewBookings(); break;
            case 3: cancelBooking(); break;
            case 4: displayQueue(); break;
            case 5: dequeue(); break;
            case 6:
                printf("\n🎥 Thank you for using our booking system! 🍿\n");
                return 0;
            default: printf("\n❌ Invalid choice. Try again!\n");
        }
    }
}
