#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Creator: Kharaj Chakraborty
int main()
{
    int i_n = 1 /*item number for counting*/, i /*loop*/, option /*main menu*/, item_types /*total number of items*/, opt2 /*return to main menu options*/, opt3 /*return to reciept entry data or main menu options*/;
    float quantity[50] /*quantity of items*/, rs[50] /*price of items*/, total_rs[50] /*price x quantity*/, gst /*Goods and Service Tax*/;
    float n_total_rs = 0 /*Net total price*/, g_total_rs /*Net total price + gst*/;
    char customer[100][1] /*Name of customer(s)*/, items[50][500] /*names of items*/, fname[1][500] /*receipt file location*/, receipt_data_txt[100][5000] /*receipt entry data file inside text*/, file_nme[1][5000] /*receipt file name to open*/, file_loc[1][5000] /*entered receipt file location*/, receipt_txt[1][5000] /*entered receipt file inside text*/;
    FILE *receipt /*receipt file (create and entry)*/, *r_data /*receipt data file (create and entry)*/, *receipt_loc /*receipt data file (read)*/, *receipt_open /*receipt file (read)*/;

    // fetch time
    time_t t = time(NULL);
    struct tm date = *localtime(&t);

start:
    // Beginning

    // select option from the main menu
    printf("=============KC RESTAURANT=============\n\n");
    printf("1. Create a new receipt\n");
    printf("2. Receipt Entry Data\n");
    printf("3. Exit\n\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    printf("\e[1;1H\e[2J"); // clear screen

    // functions of main menu options
    switch (option)
    {
    case 1:
        // Create a new receipt
        printf("Name of the customer(s): ");
        scanf("%s", customer[0]);
        printf("\n");
        printf("How many items: ");
        scanf("%d", &item_types);
        printf("\n");

        printf("\e[1;1H\e[2J");
        // clear screen

        for (i = 0; i < item_types; i++)
        {
            printf("Enter the item number %d: ", i_n);
            scanf("%s", items[i]);
            printf("\n");
            printf("Enter the price: ");
            scanf("%f", &rs[i]);
            printf("\n");
            printf("Enter the quantity: ");
            scanf("%f", &quantity[i]);
            printf("\n");
            total_rs[i] = rs[i] * quantity[i];
            i_n++;
        }

        printf("\e[1;1H\e[2J");
        // clear screen

        // Display Recipt
        printf("          KC RESTAURANT\n"
               "         Near Sitai Road,\n"
               "            Mathabhanga,\n"
               "         Coochbehar:736146\n"
               "          Ph:+91XXXXXXXXXX\n"
               "   ---------TAX INVOICE------------------\n"
               "   Date:23.10.21\n"
               "   --------------------------------------\n"
               "   Particulars   Qty Rate Amount\n"
               "   --------------------------------------\n");
        i_n = 1;
        for (i = 0; i < item_types; i++)
        {

            printf("   %d. %s       %.1f   %.1f   %.1f\n", i_n, items[i], quantity[i], rs[i], total_rs[i]);

            i_n++;
        }
        printf("   --------------------------------------\n");
        for (i = 0; i < item_types; i++)
        {
            n_total_rs = n_total_rs + total_rs[i];
        }
        printf("            Net Total: %.1f\n", n_total_rs);
        gst = (n_total_rs * 9 / 100);

        printf("            CGST @9:  %.2f \n"
               "            SGST @9:  %.2f \n",
               gst, gst);
        printf("   --------------------------------------\n");
        g_total_rs = n_total_rs + (gst * 2);
        printf("        Grand Total: %.2f\n", g_total_rs);
        printf("   --------------------------------------\n"
               "    Thank You                 Visit Again\n"
               "\n"
               "                (Take Away)\n\n\n");

        // Create Receipt File (Change The Path Below)
        sprintf(fname[0], "/Receipts/%d_%02d_%02d_%02d-%02d-%02d.txt", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec);
        receipt = fopen(fname[0], "w+");

        // Generate Receipt
        fprintf(receipt,
                "Customer(s): %s \n\n"
                "          KC RESTAURANT\n"
                "         Near Sitai Road,\n"
                "            Mathabhanga,\n"
                "         Coochbehar:736146\n"
                "          Ph:+91XXXXXXXXXX\n"
                "   ---------TAX INVOICE------------------\n"
                "   Date:23.10.21\n"
                "   --------------------------------------\n"
                "   Particulars   Qty Rate Amount\n"
                "   --------------------------------------\n",
                customer[0]);
        i_n = 1;
        for (i = 0; i < item_types; i++)
        {

            fprintf(receipt, "   %d. %s       %.1f   %.1f   %.1f\n", i_n, items[i], quantity[i], rs[i], total_rs[i]);

            i_n++;
        }
        fprintf(receipt, "   --------------------------------------\n");
        fprintf(receipt, "            Net Total: %.1f\n", n_total_rs);

        fprintf(receipt, "            CGST @9:  %.2f \n"
                         "            SGST @9:  %.2f \n",
                gst, gst);
        fprintf(receipt, "   --------------------------------------\n");
        fprintf(receipt, "        Grand Total: %.2f\n", g_total_rs);
        fprintf(receipt, "   --------------------------------------\n"
                         "    Thank You                 Visit Again\n"
                         "\n"
                         "                (Take Away)\n\n\n");

        fclose(receipt);

        // Saving Receipt Data (Change The Path Below)
        r_data = fopen("/Data/receipt_data.txt", "a+");
        fprintf(r_data, "%d_%02d_%02d_%02d-%02d-%02d.txt\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min, date.tm_sec);
        fclose(r_data);

        // Return to main menu
        printf("Enter 1 to go back or anything to exit: ");
        scanf("%d", &opt2);
        if (opt2 == 1)
        {
            printf("\e[1;1H\e[2J");
            // clear screen
            goto start;
        }
        else
        {
            exit(0);
        }
        break;

    case 2:
        // Receipt Entry Data

    r_details: // Receipt Entry Data Beginning (Change The Path Below)

        receipt_loc = fopen("/Data/receipt_data.txt", "r");

        int i = 0;

        // Displaying Receipt Entry Data File Inside Text
        while (fgets(receipt_data_txt[i], 500000, receipt_loc))
        {
            printf("%s \n", receipt_data_txt[i]);
            i++;
        }

        // Get receipt detais or return to previous option or main menu
        printf("Enter 1 To Get Receipt Details, 2 To Return to Main Menu Or Anything To Exit: ");
        scanf("%d", &opt2);
        if (opt2 == 1)
        {

            printf("\nEnter the file name: ");
            scanf("%s", file_nme[0]);
            printf("\n");

            // (Change The Path Below)
            sprintf(file_loc[0], "/Receipts/%s", file_nme[0]);

            receipt_open = fopen(file_loc[0], "r");

            int i = 0;

            // Displaying Entered Receipt File Inside Text
            while (fgets(receipt_txt[i], 500000, receipt_open))
            {
                printf("%s", receipt_txt[i]);
                i++;
            }

            fclose(receipt_open);

            // Return to previous option or main menu
            printf("Enter 1 To Get Receeipt Entry Data, 2 To Return to Main Menu Or Anything To Exit: ");
            scanf("%d", &opt3);

            if (opt3 == 1)
            {
                printf("\e[1;1H\e[2J");
                // clear screen
                goto r_details;
            }

            else if (opt3 == 2)
            {
                printf("\e[1;1H\e[2J");
                // clear screen
                goto start;
            }

            else
            {
                exit(0);
            }
        }

        else if (opt2 == 2)
        {
            printf("\e[1;1H\e[2J");
            // clear screen
            goto start;
        }

        else
        {
            exit(0);
        }

        break;

    case 3: // Exit

        exit(0);
        break;

    default: // If no options matches

        exit(0);
        break;
    }
}
