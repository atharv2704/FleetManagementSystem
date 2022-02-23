#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<strings.h>

#define I 6000
#define CARSIZE 20
#define SIZE 15
#define MAX 20

int totalTrips=0,totalKms=0;
struct customerBST *root=NULL;

struct customer
{
    char name[20];
    char surname[20];
    char gender;
    int age;
    long long int phoneNumber;
    int source;
    int destination;
};

struct places
{
    int nodeNumber;
    char cityName[20];
};

struct carQueue
{
    char vehicleNumber[12];
    char vehicleName[10];
    char chassisNumber[10];

    char driverName[12];
    int driverAge;
    long long int driverPhNumber;
};

struct hub
{
    struct carQueue q[20];
    int hubNumber;
    int fr,rear;
    int weight;
    int tripsFromHub,failedTrips;
    char hubName[20];
};

struct cars
{
    char vehicleName[10];
    char vehicleNumber[20];
    char chassisNumber[10];

    char driverName[12];
    int driverAge;
    long long int driverPhNumber;
};

struct pathStack
{
    int order[15];
    int top;
};

struct customerBST
{
    struct customerBST *lchild,*rchild;
    struct customer c;
};

struct customerBST* getNode()
{
    struct customerBST *nw=(struct customerBST*)malloc(sizeof(struct customerBST));
    nw->lchild=nw->rchild=NULL;
    return nw;
};

///Adds customer detail to BST when trip is booked
void storeCustomerRecord(struct customer record)
{
    struct customerBST *t=getNode();
    t->c=record;
    if(root==NULL)
    {
        root=t;
        return;
    }
    struct customerBST *s=root,*r;
    while(s!=NULL)
    {
        r=s;
        if(strcmp(s->c.name,record.name)>0)
        {
            s=s->lchild;
        }
        else if(strcmp(s->c.name,record.name)<0)
        {
            s=s->rchild;
        }
        else
            return;
    }
    if(strcmp(r->c.name,record.name)>0)
    {
        r->lchild=t;
    }
    else
        r->rchild=t;
}

///Finds Name of place when vertex number is passed
char* findName(struct places place[],int vertexNumber)
{
    char* placeName=(char*)malloc(sizeof(char)*20);
    int i;
    for(i=0;i<SIZE;i++)
    {
        if(place[i].nodeNumber==vertexNumber)
        {
            strcpy(placeName,place[i].cityName);
            return placeName;
        }
    }
}

///Inorder Traversal of Customer BST
void inorder(struct customerBST *root,struct places place[])
{
    if(root==NULL)
        return;
    inorder(root->lchild,place);
    printf("\t\t\t\t****************************************************\n");
    printf("Customer Full Name is:%s %s\n",root->c.name,root->c.surname);
    printf("Customer age:%d\n",root->c.age);
    printf("Customer phone number:%lld\n",root->c.phoneNumber);
    printf("Customer travelled with us from %s to %s\n",findName(place,root->c.source),findName(place,root->c.destination));
    inorder(root->rchild,place);
    return;
}

///Finds closest hub to customer source city
int minimum(int v1,int v2,int v3,int v4,int *hub)
{
    if(v1<=v2 && v1<=v3 && v1<=v4){
        *hub=0;
        return v1;
    }
    else if(v2<=v1 && v2<=v3 && v2<=v4){
        *hub=1;
        return v2;
    }
    else if(v3<=v1 && v3<=v2 && v3<=v4){
        *hub=2;
        return v3;
    }
    else{
        *hub=3;
        return v4;
    }
}

///Prints Starting car design
void printCarPattern()
{
    printf("\t\t\t\t   --***Welcome to FLEET MANAGEMENT SERVICE!***--\n");
    printf("\t\t\t\t   _________________________ \n ");
    printf("\t\t\t\t   /______________________ .. \n ");
    printf("\t\t\t\t  /   |       |     \\\        \\\ \n ");
    printf("\t\t\t\t /    |       |      \\\        \\\ \n");
    printf("\t\t\t\tC______|.......| ......\\\ _______\\\ ......... \n");
    printf("\t\t\t\t|____  | -     | -      |------   __________\\\ \n ");
    printf("\t\t\t\t              |               --  ## ____ ## \n");
    printf("\t\t\t\t/____                        _   __## ____ ## \n ");
    printf("\t\t\t\t\\\|___ <<<<<               <<<<< ____________/ \n");
    printf("\t\t\t\t     <<<<<<<------------ <<<<<<<----////---/ \n");
    printf("\t\t\t\t     <<<<<<<             <<<<<<< \n");
    printf("\t\t\t\t      <<<<<               <<<<< \n\n");
    return;
}

///Reads customer details from file and stores it
void readCustomerDetails(FILE *fp,struct customer* customersArray)
{
    //Incase file pointer isnt pointing to the file
    if(fp==NULL)
    {
        printf("Error opening customer details text file\n");
        return;
    }
    int i=0;
    while((fscanf(fp,"%s %s %c %d %lld %d %d",customersArray[i].name,customersArray[i].surname,&customersArray[i].gender,&customersArray[i].age,&customersArray[i].phoneNumber,&customersArray[i].source,&customersArray[i].destination))!=EOF)
    {
        i++;
    }
    return;
}

///Reads place vertex number and name from File
void readPlacesDetails(FILE *fp,struct places* placesArray)
{
    //Incase file pointer isnt pointing to the file
    if(fp==NULL)
    {
        printf("Error opening places text file\n");
        return;
    }
    int i=0;
    while((fscanf(fp,"%d %s",&placesArray[i].nodeNumber,placesArray[i].cityName))!=EOF)
    {
        i++;
    }
    return;
}

///Reads details specific to each car from file and stores them
void readCarsDetails(FILE *fp,struct cars* carsArray)
{
    //Incase file pointer isnt pointing to the file
    if(fp==NULL)
    {
        printf("Error opening places text file\n");
        return;
    }
    int i=0;
    while((fscanf(fp,"%s %s %s %s %d %lld",carsArray[i].vehicleName,carsArray[i].vehicleNumber,carsArray[i].chassisNumber,carsArray[i].driverName,&carsArray[i].driverAge,&carsArray[i].driverPhNumber))!=EOF)
    {
        i++;
    }
    return;
}

///Initializes queue in each hub
void initialiseHubsArray(FILE *fp,struct hub* hubsArray)
{
    int i=0;
    while((fscanf(fp,"%d %s",&hubsArray[i].hubNumber,hubsArray[i].hubName))!=EOF)
    {
        i++;
    }

    for(i=0;i<4;i++)
    {
        hubsArray[i].fr=hubsArray[i].rear=-1;
        hubsArray[i].tripsFromHub=hubsArray[i].weight=hubsArray[i].failedTrips=0;
    }
}

///Pushes node number onto stack
void push(struct pathStack *ps,int number)
{
    ps->top=ps->top+1;
    ps->order[ps->top]=number;
}
///Pops node from stack
int pop(struct pathStack *ps)
{
    int temp=ps->order[ps->top];
    ps->top=ps->top-1;
    return temp;
}
///Checks if stack is empty
int isEmpty(struct pathStack p)
{
    return p.top==-1;
}

///Prints path found from dijkstra
void printPath(int source,int destination,struct places place[],int path[])
{
    struct pathStack p;
    p.top=-1;
    //int *order=(int*)malloc(sizeof(int)*n);
    int s=destination;
    do
    {
        push(&p,s);
        s=path[s];
    }while(s!=source);
    if(p.order[p.top]!=source)
        push(&p,source);
    //printf("The shortest path is.. ");
    while(!isEmpty(p))
    {
        /*order[i]=pop(&p);
        i++;*/
        printf("%s",findName(place,pop(&p)));
        if(p.top>-1)
            printf("->");

    }
    printf("\n");
}

///Allocates cars to hubs by using weights
void assignCars(FILE *fp,struct hub* hubsArray,struct cars* carsArray)
{
    int maxWeight=INT_MIN,maxWeightedHub;
    if(fp==NULL)
    {
        printf("Error opening places text file\n");
        return;
    }
    int i=0,j=0,fleetSize=20,carsPointer=0;
    while((fscanf(fp,"%d",&hubsArray[i].weight))!=EOF)
    {
        if(hubsArray[i].weight>maxWeight)
        {
            maxWeight=hubsArray[i].weight;
            maxWeightedHub=i;
        }
        i++;
    }
    for(i=0;i<4;i++)
    {
        int assignNumber=(hubsArray[i].weight*20)/100;
        printf("Assign number for hub %d is %d\n",i,assignNumber);
        for(j=0;j<assignNumber;j++)
        {
            if(hubsArray[i].fr<0)
            {
                hubsArray[i].fr=0;
            }
            hubsArray[i].rear++;
            strcpy(hubsArray[i].q[j].vehicleName,carsArray[carsPointer].vehicleName);
            strcpy(hubsArray[i].q[j].vehicleNumber,carsArray[carsPointer].vehicleNumber);
            strcpy(hubsArray[i].q[j].chassisNumber,carsArray[carsPointer].chassisNumber);
            strcpy(hubsArray[i].q[j].driverName,carsArray[carsPointer].driverName);
            hubsArray[i].q[j].driverAge=carsArray[carsPointer].driverAge;
            hubsArray[i].q[j].driverPhNumber=carsArray[carsPointer].driverPhNumber;
            carsPointer++;
        }
    }
    //Remaining cars if any queued into max Weighted Hub
    while(carsPointer<20)
    {
        hubsArray[maxWeightedHub].rear++;
        int rear=hubsArray[maxWeightedHub].rear;
        strcpy(hubsArray[maxWeightedHub].q[rear].vehicleName,carsArray[carsPointer].vehicleName);
        strcpy(hubsArray[maxWeightedHub].q[rear].vehicleNumber,carsArray[carsPointer].vehicleNumber);
        carsPointer++;
    }
}
///Displays Car queue in each hub
void displayCarQueue(struct hub hubsArray[],struct places place[])
{

    int i,j;
    for(i=0;i<4;i++)
    {
        printf("\t\t\t\t****************************************************\n");
        printf("Cars list in Hub %s\n",findName(place,i));
        int n=hubsArray[i].rear;
        for(j=0;j<=n;j++)
        {
            printf("%s %s\n",hubsArray[i].q[j].vehicleName,hubsArray[i].q[j].vehicleNumber);
        }
    }
}

///Shortest path algorithm
void dijkstra(int distMatrix[][MAX],int n,int source,int path[],int dist[])
{
    int visited[n];
    int i,j,u,min;
    for(i=0;i<n;i++)
    {
        dist[i]=distMatrix[source][i];
        path[i]=source;
        visited[i]=0;
    }
    visited[source]=1;
    dist[source]=0;
    for(i=0;i<n-1;i++)
    {
      u=min=I;
      for(j=0;j<n;j++)
      {
          if(dist[j]<min && !visited[j])
          {
              min=dist[j];
              u=j;
          }
      }
      visited[u]=1;
      for(j=0;j<n;j++)
      {
          if(dist[j]>dist[u]+distMatrix[u][j])
          {
              dist[j]=dist[u]+distMatrix[u][j];
              path[j]=u;
          }
      }
    }
}

///If trip gets booked successfully then function acknowledges the same
void greetCustomer(struct customer customers[],int i,struct places place[])
{
    printf("\nDear %s %s thank you for booking your trip with us\n",customers[i].name,customers[i].surname);
    printf("Pickup is scheduled from city %s and destination is %s",findName(place,customers[i].source),findName(place,customers[i].destination));
}

///Calculates which hub should the query be serviced from and executes it
void serviceCustomer(int distMatrix[][MAX],int source,int destination,struct hub* hubsArray,struct places place[],struct customer customers[],int i)//Add message greeting customer by name
{
    int dist0[SIZE],dist1[SIZE],dist2[SIZE],dist3[SIZE],dist[SIZE],distToSource,nearestHub;
    int path0[SIZE],path1[SIZE],path2[SIZE],path3[SIZE],path[SIZE];
    char *hubName=(char *)malloc(sizeof(char)*20);
    char vehicleName[10],vehicleNumber[20];
    dijkstra(distMatrix,15,0,path0,dist0);
    dijkstra(distMatrix,15,1,path1,dist1);
    dijkstra(distMatrix,15,2,path2,dist2);
    dijkstra(distMatrix,15,3,path3,dist3);
    distToSource=minimum(dist0[source],dist1[source],dist2[source],dist3[source],&nearestHub);
    hubName=findName(place,nearestHub);
    if(hubsArray[nearestHub].fr<0 || hubsArray[nearestHub].fr>hubsArray[nearestHub].rear)
    {
        printf("\nSorry cant serve the city %s currently as cars are exhausted from nearest hub %s\n",findName(place,source),hubName);
        hubsArray[nearestHub].failedTrips++;
        return;
    }

    totalKms += distToSource;
    hubsArray[nearestHub].tripsFromHub++;
    totalTrips++;
    storeCustomerRecord(customers[i]);
    int front=hubsArray[nearestHub].fr;
    strcpy(vehicleName,hubsArray[nearestHub].q[front].vehicleName);
    strcpy(vehicleNumber,hubsArray[nearestHub].q[front].vehicleNumber);
    hubsArray[nearestHub].fr++;
    greetCustomer(customers,i,place);
    printf("\nVehicle %s with Vehicle Number %s and driver %s is leaving hub %s",vehicleName,vehicleNumber,hubsArray[nearestHub].q[front].driverName,findName(place,nearestHub));
    printf("\nDriver Contact Number is %lld",hubsArray[nearestHub].q[front].driverPhNumber);
    printf("\nPreferred path to customers pick up city would be:");
    if(nearestHub==0)
    {
        printPath(nearestHub,source,place,path0);
    }
    else if(nearestHub==1)
    {
        printPath(nearestHub,source,place,path1);
    }
    else if(nearestHub==2)
    {
        printPath(nearestHub,source,place,path2);
    }
    else
    {
        printPath(nearestHub,source,place,path3);
    }
    dijkstra(distMatrix,15,source,path,dist);
    //print path from source to destination
    printf("Preferred route to reach customer to destination would be:");
    printPath(source,destination,place,path);
    printf("WISHING YOU A SAFE AND ENJOYABLE JOURNEY :)\n");
    printf("\t\t\t\t****************************************************\n");
}

///Prints all vehicle details
void printVehicleDetails(struct cars car[])
{
    int i;
    printf("\t\t\t\t****************************************************\n");
    printf("Details of Entire Fleet/Cars under operation is:\n");
    for(i=0;i<20;i++)
    {
        //printf("\n#######\n");
        printf("Car Name:%s\n",car[i].vehicleName);
        printf("Car Number:%s\n",car[i].vehicleNumber);
        printf("Car Chassis Number:%s\n",car[i].chassisNumber);
        printf("\n#######\n");
    }
    printf("\t\t\t\t*****************************************************\n");
}

///Searches in BST if customer data is present
void searchCustomer(struct places place[])
{
    char name[20];
    printf("Enter Name you want to search:\n");
    scanf("%s",name);
    struct customerBST* t=root;
    while(t!=NULL)
    {
        if(strcmp(t->c.name,name)>0)
        {
            t=t->lchild;
        }
        else if(strcmp(t->c.name,name)<0)
        {
            t=t->rchild;
        }
        else if(strcmp(t->c.name,name)==0)
        {
            printf("Customer details found:\n");
            printf("Customer Full Name is:%s %s\n",t->c.name,t->c.surname);
            printf("Customer age:%d\n",t->c.age);
            printf("Customer phone number:%lld\n",root->c.phoneNumber);
            printf("Customer travelled with us from %s to %s\n",findName(place,t->c.source),findName(place,t->c.destination));
            break;
        }
    }
    if(t==NULL)
        printf("Customer details not found in Database\n");
    return;
}

///Prints all driver details
void printDriverDetails(struct cars car[])
{
    int i;
    printf("\t\t\t\t****************************************************\n");
    printf("Details of Drivers working in the organization is:\n");
    for(i=0;i<20;i++)
    {
        //printf("\n#######\n");
        printf("Driver Name:%s\n",car[i].driverName);
        printf("Driver Age:%d\n",car[i].driverAge);
        printf("Driver Contact Number:%lld\n",car[i].driverPhNumber);
        printf("\n#######\n");
    }
    printf("\t\t\t\t*****************************************************\n");
}

///Prints details of the day
void printReport()
{
    printf("\t\t\t\t****************************************************\n");
    printf("  Total kilometers travelled by complete fleet is %d\n",totalKms);
    printf("  Total trips completed by fleet is %d\n",totalTrips);
    printf("\t\t\t\t****************************************************\n");
}

///Generates P&L Report
void generatePLStatement()
{
    printf("\t\t\t\t****************************************************\n");
    printf("Presumptions made are:\n");
    printf("1. Fuel Cost fixed at 80 rupees per liter\n");
    printf("2. Mileage of entire fleet on average 15 kilometers per liter\n");
    printf("3. Organization's earnings are taxed 10%% on income generated\n");//Using 2 percentage signs to escape single % sign
    printf("4. Fare rate is 20 rupees per kilometer\n");
    printf("5. Organization sets aside another 10%% for annual maintenance of fleet\n");//Using 2 percentage signs to escape single % sign
    printf("6. Driver salary and Motorway Tolls if any are paid by customer\n");

    int revenue=totalKms*20,fuelExpense=(totalKms*80)/15,annualMaintenance=revenue*0.1,tax=annualMaintenance,profit;
    profit=revenue-fuelExpense-annualMaintenance-tax;
    printf("\n#Revenue Generated is:%d\n",revenue);
    printf("#Fuel Expense:%d\n",fuelExpense);
    printf("#Annual Maintenance Cost:%d\n",annualMaintenance);
    printf("#Income Tax:%d\n",tax);
    printf("\nFinal Profit After Tax and expense is:%d\n",profit);
    printf("\t\t\t\t****************************************************\n");
    return;
}

///Calculates new weights with 75% weightage to existing weight and 25% new weight
//Take file input to write to file
void calculateWeights(FILE *fp,struct hub* hubsArray)
{
    int i,newWeight,trips;
    int finalWeight[4];
    for(i=0;i<4;i++)
    {
        trips=hubsArray[i].failedTrips+hubsArray[i].tripsFromHub;
        //newWeight=(hubsArray[i].tripsFromHub*100)/totalTrips;
        newWeight=(trips*100)/totalTrips;
        //Assigning 75% weightage to earlier weight and only 25% weightage to new weight
        //finalWeight[i]=floor((3*hubsArray[i].weight + newWeight)/4);
        finalWeight[i]=(3*hubsArray[i].weight + newWeight)/4;
    }
    i=0;
    //printf("Trips from bangalore is :%d\n",hubsArray[0].tripsFromHub);
    while(i<4)
    {
        printf("Final Weight of Hub %d is:%d\n",i,finalWeight[i]);
        fprintf(fp,"%d\n",finalWeight[i]);
        i++;
    }
}

///Initialize adjacency matrix
void initialiseDistanceMatrix(int distMatrix[][MAX])
{
    int i,j;
    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            if(i==j)
                distMatrix[i][j]=0;
            else
                distMatrix[i][j]=I;
        }
    }
}

///Create adjacency matrix
void generateDistanceMatrix(FILE *fp,int distMatrix[][MAX])
{
    int vertex1,vertex2,distance;
    while((fscanf(fp,"%d %d %d",&vertex1,&vertex2,&distance))!=EOF)
    {
        distMatrix[vertex1][vertex2]=distance;
        distMatrix[vertex2][vertex1]=distance;
    }
    return;
}


int main()
{
    struct customer customers[25];
    struct places place[16];
    struct hub hubs[4];
    struct cars car[CARSIZE];
    int distMatrix[MAX][MAX],i=0;
    FILE *customerFile,*test,*carsFile,*placesFile,*distanceFile,*hubsFile,*hubWeightFile;

    printCarPattern();

    customerFile=fopen("Cust.txt","r");
    readCustomerDetails(customerFile,customers);
    fclose(customerFile);

    carsFile=fopen("Cars.txt","r");
    readCarsDetails(carsFile,car);
    fclose(carsFile);

    placesFile=fopen("Place.txt","r");
    readPlacesDetails(placesFile,place);
    fclose(placesFile);

    initialiseDistanceMatrix(distMatrix);
    distanceFile=fopen("Distance.txt","r");
    generateDistanceMatrix(distanceFile,distMatrix);
    fclose(distanceFile);

    hubsFile=fopen("Hubs.txt","r");
    initialiseHubsArray(hubsFile,hubs);
    fclose(hubsFile);

    hubWeightFile=fopen("HubWeight.txt","r");
    assignCars(hubWeightFile,hubs,car);
    fclose(hubWeightFile);

    int ch;
    while(1)
    {
        printf("\n Enter:\n 1-Show car list in hubs\n 2-Service Customer\n 3-Service all customers\n 4-Details of the Day\n 5-Customers Details\n 6-Search customer by name\n 7-Vehicle Details\n 8-Driver Details\n 9-P&L statement\n 10-Calculate new weights\n 11-Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:displayCarQueue(hubs,place);
                    break;
            case 2:serviceCustomer(distMatrix,customers[i].source,customers[i].destination,hubs,place,customers,i);
                    i++;
                    break;
            case 3:for(;i<20;i++)
                    {
                        serviceCustomer(distMatrix,customers[i].source,customers[i].destination,hubs,place,customers,i);
                    }
                    break;
            case 4: printReport();
                    break;
            case 5:inorder(root,place);
                    break;
            case 6:searchCustomer(place);
                    break;
            case 7:printVehicleDetails(car);
                    break;
            case 8:printDriverDetails(car);
                    break;
            case 9:generatePLStatement();
                    break;
            case 10:hubWeightFile=fopen("HubWeight.txt","w");
                    calculateWeights(hubWeightFile,hubs);
                    fclose(hubWeightFile);
                    break;
            case 11:break;
        }
        if(ch==11) break;
    }
    return 0;
}
