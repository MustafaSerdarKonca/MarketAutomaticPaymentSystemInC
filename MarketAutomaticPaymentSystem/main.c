#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct productInformation{

    char productName[200];
    char category[200];
    float unitPrice;
    int barcode;

};

void printer (struct productInformation *product){
    float totalAmount = 0;
    while(1==1){

        int productReceived;
        int amount, selection;
        time_t timeInfo = time(NULL);

        FILE *dekont, *invoice;

        dekont = fopen("dekont.txt", "r");
        invoice = fopen("invoice.txt", "a+");
        printf("\n");
        printf("Please Enter the Barcode of The Product You Want to Buy ---> ");
        scanf("%d", &productReceived);

        printf("Please Enter How Many You Want to Buy ---> ");
        scanf("%d", &amount);

        printf("\n");
        printf("Your Product Has Been Successfully Added to Your Invoice.\n\n\n");

        while(!feof(dekont)){

            fscanf(dekont,"%s %s %f %d\n", &(*product).productName,&(*product).category, &(*product).unitPrice, &(*product).barcode);

                if((*product).barcode == productReceived){

                    totalAmount += (*product).unitPrice*amount;

                    fprintf(invoice , "%s\t\t%s\t\t%.2f\t\t%d\t\t%s", (*product).productName,(*product).category, (*product).unitPrice*amount, (*product).barcode, ctime(&timeInfo));
                    rewind(invoice);

                }

        }

        printf("Press 0 to Exit or Press Any Number ---> ");
        scanf("%d", &selection);

        if(selection==0){

            printf("\n\t\tWe Thank You For Choosing Us In Your Shopping.\nYour Products Have Been Processed Into the invoice.txt File With Their Dates, Please Check.\n\n");
            fprintf(invoice , "\n\n%s\t\t\t%.2f\n", "Total Amount",totalAmount);
            fprintf(invoice , "%s\n\n", "-------------------------------------------- o --------------------------------------------");
            break;
        }
    }
}

void scanner (struct productInformation *product){

    FILE *dekont;
    if ((dekont = fopen("dekont.txt", "r")) == NULL){

    printf("Unable to Open the File!\n");
    exit(1);
    }

    printf("\n|Product Name| |Category|    |Unit Price|     |Barcode|\n\n");
    for(;;){

        fscanf(dekont,"%s %s %f %d\n", &(*product).productName,&(*product).category, &(*product).unitPrice, &(*product).barcode);
        printf("%s\t\t%s\t\t%.2f\t\t%d\n", (*product).productName,(*product).category, (*product).unitPrice, (*product).barcode);

        if (feof(dekont))
            break;
    }
}
void addingProducts (struct productInformation *productInfoPointer){

    int selection;

    while(1==1){

        printf("-----------------------| Welcome to Add Products Screen |-----------------------\n\n\n");

        printf("Enter the Name of the Product You Want to Add, Please ---> ");
        scanf("%s",(*productInfoPointer).productName);

        printf("Enter the Category of the Product You Want to Add, Please ---> ");
        scanf("%s",(*productInfoPointer).category);

        printf("Enter the Unit Price of the Product You Want to Add, Please ---> ");
        scanf("%f", &(*productInfoPointer).unitPrice);

        srand(time(NULL));
        (*productInfoPointer).barcode = rand()%1000+100;

        printf("\n--------------------------------------| o |-------------------------------------\n\n");
        printf("New Product Created.\n");
        printf("Product Barcode is %d\n", (*productInfoPointer).barcode);
        printf("\n--------------------------------------| o |-------------------------------------\n\n");

        FILE *products;
        products = fopen("dekont.txt", "a+");

        fprintf(products , "%s\t\t%s\t\t%.2f\t\t%d\n", (*productInfoPointer).productName,(*productInfoPointer).category, (*productInfoPointer).unitPrice, (*productInfoPointer).barcode);
        rewind(products);
        fclose(products);


        printf("Press 0 to Exit or Press Any Number ---> ");
        scanf("%d", &selection);
        printf("\n");

        if(selection==0)
            break;
    }
}

int main()
{
    struct productInformation productInfo;

    while(1){

        printf("-----------------------| Welcome to Market Automated Payment System |-----------------------\n\n");

        printf("1-) Add Products\n");
        printf("2-) List Products\n");
        printf("3-) Buy Products\n\n\n");
        printf("What Would You Like to Do ---> ");

        int selection;

        scanf("%d", &selection);

        switch(selection){

            case 1:

                printf("\n\n");
                addingProducts(&productInfo);
                break;
            case 2:

                scanner(&productInfo);
                break;

            case 3:

                scanner(&productInfo);
                printer(&productInfo);

                FILE *invoice;
                time_t timeInfo = time(NULL);

                invoice = fopen("invoice.txt", "r");

                for(;;){

                struct productInformation *p;
                p = (struct productInformation*) malloc(sizeof(struct productInformation));

                fscanf(invoice,"%s %s %f %d\n ", &(*p).productName,&(*p).category, &(*p).unitPrice, &(*p).barcode, (*p).barcode);

                if (feof(invoice))
                    break;
                }

                break;
        }

        break;

    }
}
