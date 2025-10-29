#include <stdio.h>
#include <string.h>

#define ROWS 4
#define COLS 5
#define MAX_BOOKINGS 10
#define MAX_QUEUE 5

// Structure to store each booking
struct Booking {
    int id;
    char movie[30];
    int seats[ROWS][COLS];
    int seat_count;
    int date;
    int time_choice;
    float total;
};

// Global data
struct Booking bookings[MAX_BOOKINGS];
int booking_count = 0;
int queue[MAX_QUEUE];
int front = -1, rear = -1;
int seat_map[ROWS][COLS] = {0};

// Function declarations
void showSeats();
void bookTicket();
void enqueue(int id);
void dequeue();
void showQueue();
void viewBookings();

void showSeats() {
    printf("\nSeat Layout (4x5):\n");
    printf("Green = Available | Red = Booked\n\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (seat_map[i][j] == 0)
                printf("[G] ");
            else
                printf("[R] ");
        }
        printf("\n");
    }
}

void enqueue(int id) {
    if (rear == MAX_QUEUE - 1) {
        printf("\n⚠️ Queue Full! Wait for next show.\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = id;
    printf("✅ Booking %d added to processing queue.\n", id);
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("\n⚠️ No bookings to process.\n");
        return;
    }
    printf("\n✅ Processed Booking ID %d removed from queue.\n", queue[front]);
    front++;
}

void showQueue() {
    if (front == -1 || front > rear) {
        printf("\n📋 Queue Empty.\n");
        return;
    }
    printf("\n📋 CURRENT QUEUE:\n");
    for (int i = front; i <= rear; i++)
        printf("Booking ID: %d\n", queue[i]);
}

void viewBookings() {
    if (booking_count == 0) {
        printf("\n📋 No bookings yet.\n");
        return;
    }
    printf("\n🎟️ ALL BOOKINGS:\n");
    for (int i = 0; i < booking_count; i++) {
        printf("------------------------------\n");
        printf("Booking ID : %d\n", bookings[i].id);
        printf("Movie      : %s\n", bookings[i].movie);
        printf("Seats Booked: %d\n", bookings[i].seat_count);
        printf("Date       : %d Oct 2025\n", bookings[i].date);
        printf("Show Time  : Option %d\n", bookings[i].time_choice);
        printf("Total Bill : Rs. %.2f\n", bookings[i].total);
    }
    printf("------------------------------\n");
}

void bookTicket() {
    char movies[3][30] = {"Spiderman", "Made In India", "3 Idiots"};
    int movie_id, date, time_choice, count = 0;

    printf("\nAvailable Movies:\n");
    printf("1. Spiderman\n2. Made In India\n3. 3 Idiots\n");
    printf("Enter movie ID: ");
    scanf("%d", &movie_id);

    if (movie_id < 1 || movie_id > 3) {
        printf("❌ Invalid movie selection.\n");
        return;
    }

    showSeats();
    printf("\nHow many seats to book (max %d)? ", ROWS * COLS);
    scanf("%d", &count);

    int selected = 0;
    for (int i = 0; i < ROWS && selected < count; i++) {
        for (int j = 0; j < COLS && selected < count; j++) {
            if (seat_map[i][j] == 0) {
                seat_map[i][j] = 1;
                selected++;
            }
        }
    }

    printf("Enter date (e.g. 15 for 15th Oct): ");
    scanf("%d", &date);
    printf("Select show time (1=10:30AM, 2=1:30PM, 3=3:30PM, 4=7PM): ");
    scanf("%d", &time_choice);

    float total = count * 350.0;

    struct Booking b;
    b.id = 1000 + booking_count + 1;
    strcpy(b.movie, movies[movie_id - 1]);
    b.date = date;
    b.time_choice = time_choice;
    b.seat_count = count;
    b.total = total;
    memcpy(b.seats, seat_map, sizeof(seat_map));

    bookings[booking_count++] = b;
    printf("\n✅ Booking successful! ID = %d\n", b.id);
    printf("💰 Total Bill: Rs. %.2f\n", total);
    enqueue(b.id);
}

int main() {
    int choice;
    printf("*******************************************\n");
    printf("   🎬 MOVIE TICKET BOOKING SYSTEM (C) 🎟️   \n");
    printf("*******************************************\n");

    while (1) {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Book Ticket\n");
        printf("2. View Bookings\n");
        printf("3. View Queue\n");
        printf("4. Process Booking (Dequeue)\n");
        printf("5. View Seats\n");
        printf("6. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: viewBookings(); break;
            case 3: showQueue(); break;
            case 4: dequeue(); break;
            case 5: showSeats(); break;
            case 6: printf("\n🎥 Thank you for using the system! 🍿\n"); return 0;
            default: printf("❌ Invalid choice!\n");
        }
    }
}
