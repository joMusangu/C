#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 10
#define DAY_RATE 50

struct Customer {
    char username[20];
    char lastName[20];
    char email[50];
    char address[50];
    char telephone[15];
};

struct Room {
    int roomNumber;
    int status; // 0 = vacant, 1 = reserved
    struct Customer customer;
    char checkInDate[11];
    char checkOutDate[11];
};

void initializeRooms(struct Room rooms[]) {
    int i;
    for (i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].status = 0;
    }
}

void printCustomerDetails(struct Customer customer) {
    printf("Name: %s %s\n", customer.username, customer.lastName);
    printf("Email: %s\n", customer.email);
    printf("Address: %s\n", customer.address);
    printf("Telephone: %s\n", customer.telephone);
}

void bookRoom(struct Room rooms[]) {
    int roomNumber, i;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);

    // Check if room is vacant
    if (rooms[roomNumber - 1].status == 1) {
        printf("Room already booked\n");
        return;
    }

    // Input customer details
    struct Customer customer;
    printf("Enter customer details:\n");
    printf("Username: ");
    scanf("%s", customer.username);
    printf("Last name: ");
    scanf("%s", customer.lastName);
    printf("Email: ");
    scanf("%s", customer.email);
    printf("Address: ");
    scanf("%s", customer.address);
    printf("Telephone: ");
    scanf("%s", customer.telephone);

    // Input check-in and check-out dates
    char checkInDate[11], checkOutDate[11];
    printf("\nEnter check-in date (YYYY-MM-DD): ");
    scanf("%s", checkInDate);
    printf("\nEnter check-out date (YYYY-MM-DD): ");
    scanf("%s", checkOutDate);

    // Update room status and details
    rooms[roomNumber - 1].status = 1;
    rooms[roomNumber - 1].customer = customer;
    strcpy(rooms[roomNumber - 1].checkInDate, checkInDate);
    strcpy(rooms[roomNumber - 1].checkOutDate, checkOutDate);

    printf("Room %d booked successfully\n", roomNumber);
}


void viewCustomerDetails(struct Room rooms[]) {
    int roomNumber, i;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);

    // Check if room is vacant
    if (rooms[roomNumber - 1].status == 0) {
        printf("Room is vacant\n");
        return;
    }

    // Print customer details
    printf("Customer details for room %d:\n", roomNumber);
    printCustomerDetails(rooms[roomNumber - 1].customer);
}

void editCustomerDetails(struct Room rooms[]) {
    int roomNumber, i;
    printf("Enter room number: ");
    scanf("%d", &roomNumber);

    // Check if room is vacant
    if (rooms[roomNumber - 1].status == 0) {
        printf("Room is vacant\n");
        return;
    }

    // Input new customer details
    struct Customer customer;
    printf("Enter new customer details:\n");
    printf("Username: ");
    scanf("%s", customer.username);
    printf("Last name: ");
    scanf("%s", customer.lastName);
    printf("Email: ");
    scanf("%s", customer.email);
    printf("Address: ");
    scanf("%s", customer.address);
    printf("Telephone: ");
    scanf("%s", customer.telephone);

// Update customer details
rooms[roomNumber - 1].customer = customer;

printf("Customer details for room %d updated successfully\n", roomNumber);
}

void checkOut(struct Room rooms[]) {
int roomNumber, i;
printf("Enter room number: ");
scanf("%d", &roomNumber);
// Check if room is vacant
if (rooms[roomNumber - 1].status == 0) {
    printf("Room is already vacant\n");
    return;
}

// Calculate bill based on number of days stayed
int daysStayed;
printf("Enter number of days stayed: ");
scanf("%d", &daysStayed);
int bill = daysStayed * DAY_RATE;

// Update room status and clear customer details
rooms[roomNumber - 1].status = 0;
strcpy(rooms[roomNumber - 1].checkInDate, "");
strcpy(rooms[roomNumber - 1].checkOutDate, "");
struct Customer emptyCustomer = {"", "", "", "", ""};
rooms[roomNumber - 1].customer = emptyCustomer;

printf("Room %d checked out successfully\n", roomNumber);
printf("Bill for room %d: $%d\n", roomNumber, bill);
}

void printReport(struct Room rooms[]) {
FILE *file;
file = fopen("hotel.txt", "w");
if (file == NULL) {
    printf("Error creating file\n");
    return;
}

int i;
for (i = 0; i < MAX_ROOMS; i++) {
    fprintf(file, "Room number: %d\n", rooms[i].roomNumber);
    if (rooms[i].status == 0) {
        fprintf(file, "Status: Vacant\n");
    } else {
        fprintf(file, "Status: Reserved\n");
        fprintf(file, "Customer details:\n");
        printCustomerDetails(rooms[i].customer);
        fprintf(file, "Check-in date: %s\n", rooms[i].checkInDate);
        fprintf(file, "Check-out date: %s\n", rooms[i].checkOutDate);
    }
    fprintf(file, "\n");
}

printf("Report printed successfully to hotel.txt\n");
fclose(file);
}

int main() {
struct Room rooms[MAX_ROOMS];
initializeRooms(rooms);
char transactionType;
do {
    printf("Transaction type? (B - Book a room, V - View customer details, E - Edit customer details, C - Check-out, R - Print report, X - Exit): ");
    scanf(" %c", &transactionType);

    switch (transactionType) {
        case 'B':
        case 'b':
            bookRoom(rooms);
            break;
        case 'V':
        case 'v':
            viewCustomerDetails(rooms);
            break;
        case 'E':
        case 'e':
            editCustomerDetails(rooms);
            break;
        case 'C':
        case 'c':
            checkOut(rooms);
            break;
        case 'R':
        case 'r':
            printReport(rooms);
            break;
        case 'X':
        case 'x':
            printf("Exiting program\n");
            break;
        default:
            printf("Invalid transaction type\n");
    }
} while (transactionType != 'X' && transactionType != 'x');
return 0;
}

