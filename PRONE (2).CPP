#include<iostream.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
void time();
void title();
void reservation();
void reservationdet();
void fselect();
void tselect();
void bselect();
int search(int,int,int);
void billing(int);
void town(int);
int start=0,
    end=0,
    mode=0,
    id=0;

//Defining cities as codes
void town(int s)
{
 if(s==1)
 cout<<"New Delhi";
 if(s==2)
 cout<<"Chennai";
 if(s==3)
 cout<<"Mumbai";
 if(s==4)
 cout<<"Kolkata";
 if(s==5)
 cout<<"Hyderabad";
 if(s==6)
 cout<<"Bangalore";
 if(s==7)
 cout<<"Panaji";
 if(s==8)
 cout<<"Cochin";
}

//Individual customer data
struct customer
{
 char name[20];
 int id;
 int startc,endc,modec,age,ccno,ct,type,route,date,month;
 float billamt;
}pass[1000];

//Heade for page
void header()
{
 clrscr();
 title() ;
 time()  ;
}

 void time()
{
 char*date;
 time_t timer;
 timer=time(NULL);
 date=asctime(localtime(&timer));
 printf("\n\n                                                        %s",date);
}

void title()
{
 cout<<" \t \t \t ";
 cout<< "A.J.V. Tours and Travels";
}

//Flight Timetables
struct flight
{
 char Fromf[12] , Tof[12];
 int fdist,flno;
 int fseatsavlf,fseatsavle;
 int fdept,farr ;
 float afeprice,cfeprice,affprice,cffprice,ftime;
} fl[]=  {  {"Chennai","Delhi",1474,121,30,180,3000,3145,3949,3144.6,6500,5949,1.45 } ,
	    {"Delhi","Chennai",1474,112,30,180,3600,3745,3949,3144.6,6500,5949,1.45 } ,
	    {"Delhi","Kolkata",1305,114,20,130,1800,1930,2610,2349,5500,4610,1.30   } ,
	    {"Kolkata","Delhi",1305,141,20,130,3400,3530,2610,2349,5500,4610,1.30   } ,
	    {"Delhi","Mumbai" ,1155,113,10,55, 1200,1315,2310,2079,4750,4310,1.15   } ,
	    {"Mumbai","Delhi" ,1155,131,10,55, 3200,3315,2310,2079,4750,4310,1.15   } ,
	    {"Mumbai","Chennai",1030,132,5,40,3800,3910,2060,1854,4200,4060,1.10    } ,
	    {"Chennai","Mumbai",1030,123,5,40,1400,1510,2060,1854,4200,4060,1.10    } ,
	    {"Mumbai","Kolkata",1666,134,50,200,2200,2355,3332,2998.8,7000,6332,1.55} ,
	    {"Kolkata","Mumbai",1666,143,50,200,1600,1755,3332,2998.8,7000,6332,1.55} ,
	    {"Kolkata","Chennai",1355,142,20,130,1000,1140,2710,2439,5500,5310,1.40 } ,
	    {"Chennai","Kolkata",1355,124,20,130,2000,2140,2710,2439,5500,5310,1.40 }};


//Train Rate conversions
int cteprice=0.2,ateprice=0.3;//Cost per kilometre for economy
int ctfprice=0.10,atfprice=0.13;//Cost per kilometre for first class

//Train Timetables
struct train
{
 char fromt[12],tot[12];
 int tdist,tno;
 int tseatsavlf,tseatsavle;//static so that seats dont return to same value
 int tdept,tarr;
 float timeh;//timeh for hours and timem for minutes
}t[]={ { "Chennai" ,"Delhi"   ,2716,12021,600,750,1215,3615,42     } ,
       { "Delhi"   ,"Chennai" ,2716,12012,600,750,3715,3115,42     } ,
       { "Delhi"   ,"Kolkata" ,1461,12014,600,750,1300,3650,17.50  } ,
       { "Kolkata" ,"Delhi"   ,1461,12041,600,750,1710,1050,17.50  } ,
       { "Delhi"   ,"Mumbai"  ,1367,12013,600,750,1640,3830,15.50  } ,
       { "Mumbai"  ,"Delhi"   ,1367,12031,600,750,1726,3940,16.14  } ,
       { "Mumbai"  ,"Chennai" ,1281,12032,600,750,1400,3750,17.50  } ,
       { "Chennai" ,"Mumbai"  ,1281,12023,600,750,1200,3550,17.50  } ,
       { "Mumbai"  ,"Kolkata" ,1966,12034,600,750,3600,1200,30.0   } ,
       { "Kolkata" ,"Mumbai"  ,1966,12043,600,750,1700,2300,30.0   } ,
       { "Kolkata" ,"Chennai" ,1661,12042,600,750,3800,3450,20.50  } ,
       { "Chennai" ,"Kolkata" ,1661,12024,600,750,1110,3800,20.50  }};

//Bus Timetables
struct bus
{
 char fromb[12],tob[12];
 int bdist,bno,bseatsavlf,bseatsavle,bdept,barr;
 float abeprice,cbeprice,abfprice,cbfprice ,time;
} bus[]={  {"Chennai","Hyberabad",375,25,40,40,2000,2345,455,300,600,576,3.45 },
	   {"Hyderabad","Chennai",375,52,40,40,1800,2145,550,455,390,576,3.45 },
	   {"Delhi","Kolkata",1305,14,55,55,1400,1700,400,395,550,450,3.00    },
	   {"Kolkata","Delhi",1305,41,55,55,1500,1800,450,395,550,450,3.00    },
	   {"Chennai","Cochin",300,28,45,45,2130,3430,450,390,500,400,6.00    },
	   {"Cochin","Chennai",300,82,45,45,2030,3230,450,390,500,400,4.00    },
	   {"Chennai","Bangalore",395,26,50,50,2245,3545,400,395,550,444,7.00 },
	   {"Bangalore","Chennai",395,62,50,50,3245,3645,400,395,550,444,4.00 },
	   {"Hyderabad","Banglore",200,56,54,54,3100,3500,500,450,600,456,4.00},
	   {"Banglore","Hyderabad",200,65,51,51,3300,3700,550,450,600,456,4.00},
	   {"Mumbai","Panaji",250,37,34,34,1800,3000,600,450,650,445,6.00     },
	   {"Panaji","Mumbai",250,73,44,44, 1200,3400,650,450,700,445,4.00   }};



//To find the apt route for the user
int search(int a , int b, int c)
{
 int find , i,st=0,ret;

  if(c==1)
   for(i=0;i<12;i++)
    {
     if(fl[i].flno==(100+(a*10)+b))
     find=i;st=1;
    }
  if(c==2)
   for(i=0;i<12;i++)
    {
     if(t[i].tno==(12000+(a*10)+b))
     find=i;st=1;
    }
  if(c==3)
   for(i=0;i<15;i++)
    {
     if(bus[i].bno==a*10+b)
     find=i;st=1;
    }

 if(st)
 ret=find;
 else
 ret=-1;

 return(ret);
}



//Home page
void home()
{
 header();
x:char a ;
 cout<<"\n \n \n \n ";
 cout<<"\n                          1.Ticket Reservation";

 cout<<"\n\n\n\nHelp: \n  a)About \n  b)Exit";
 cout<<"\n\n\n\n     Your choice:";
 cin>>a ;
 switch(a)
 {
 case '1':
 reservation();
 break;
 case '2':
 cout<<"\n Service unavailable!";
 break;
 case 'a': case 'A' :
 cout<<"Welcome to A.J.V. tours and travels";
 cout<<"\n For booking select one option by typing the number corresponding to it.";
 goto x;
 case 'b' : case 'B':
 cout<<"";
 break;

 default:cout<<"\n Please select the right option.";
 }
}

//Reservation type selection
void reservation()
{
    char i;
    header();
    cout<<"\n\n\n";
    cout<<"\n                          1.Railway Reservation";
    cout<<"\n\n                          2.Airway  Reservation";
    cout<<"\n\n                          3.Bus Reservation\n\n\n  ";
    cout<<"\n\n\n\n\n\n     Your choice:";
    cin>>i;
    switch(i)
    {
    case '1':
    tselect();
    break;
    case '2':
    fselect();
    break;
    case '3':
    bselect();
    break;
    default:
    cout<<"\n Please enter the right choice!";
    }
}

//Flight city selection
void fselect()
{
 header();
sf:int fboar , fdest, cfm;
 cout<<"\n 1.Delhi-Indira Gandhi Intl";
 cout<<"\n 2.Chennai-Kamraj Intl";
 cout<<"\n 3.Mumbai-Chattrapathi Shivaji Intl";
 cout<<"\n 4.Kolkata-Netaji Subash Chandra Bose Intl";
 cout<<"\n\n\nEnter boarding airport no:";cin>>fboar;
 cout<<"\nEnter Destination airport no:";cin>>fdest;
 cout<<"\n\n Confirm?(1-yes/0-no)";cin>>cfm;
 if(!cfm)
  {
   clrscr();
   header();
   cout<<" Ok , try again!";
   goto sf;
  }
 else if(fboar==fdest)
  {
   clrscr();
   header();
   cout<<" Please enter a different destination!";
   goto sf;
  }
 else if(fboar>4||fdest>4)
   {
    clrscr();
    header();
    cout<<" Please enter a valid choice!";
    goto sf;
   }
 else if(cfm)
   {
    mode = 1;
    ::start = fboar;
    ::end = fdest;
    reservationdet();
    } 
}




//Train city selection
void tselect()
{
 header();
st:int tboar , tdest, cfm;
 cout<<"\n 1.Delhi";
 cout<<"\n 2.Chennai";
 cout<<"\n 3.Mumbai";
 cout<<"\n 4.Kolkata";
 cout<<"\n\n\nEnter boarding city no:";cin>>tboar;
 cout<<"\nEnter Destination city no:";cin>>tdest;
 cout<<"\n\n Confirm?(1-yes/0-no)";cin>>cfm;
 if(!cfm)
  {
   clrscr();
   header();
   cout<<" Ok , try again!";
   goto st;
  }

 else if(tboar==tdest)
  {
   clrscr();
   header();
   cout<<" Please enter a different destination!";
   goto st;
  }
 else if(tboar>4||tdest>4)
   {
    clrscr();
    header();
    cout<<" Please enter a valid choice!";
    goto st;
   }
 else if(cfm)
   {
    mode = 2;
    ::start = tboar;
    ::end = tdest;
    reservationdet();
   }
}

//Bus city selection
void bselect()
{
a: header();
sb:int bboar,bdest,cfm;
 cout<<"\n 1.New Delhi-Nehru bus terminus";
 cout<<"\n 2.Chennai-Cmbt bus terminus";
 cout<<"\n 3.Mumbai-Chattrapathi shivaji bus terminus";
 cout<<"\n 4.Kolkata-Bagdogra bus terminus";
 cout<<"\n 5.Hyderabad-Charminar bus terminus";
 cout<<"\n 6.Bangalore-Majestic bus terminus";
 cout<<"\n 7.Panaji-Rambara bus terminus";
 cout<<"\n 8.Cochin-Cochin bus terminus";
 cout<<"\n\n Only select routes are available";
 cout<<"\n Avlbl acc to city no:";
 cout<<"\n 2<->5,1<->4,2<->8,2<->6,5<->6,3<->7";
 cout<<"\n\n\nEnter boarding city no:";cin>>bboar;
 cout<<"\nEnter Destination  city no:";cin>>bdest;
 cout<<"\n\n Confirm?(1-yes/0-no)";cin>>cfm;
 if(!cfm)
  {
   clrscr();
   header();
   cout<<" Ok , try again!";
   goto sb;
  }

 else if(bboar==bdest)
  {
   clrscr();
   header();
   cout<<" Please enter a different destination!";
   goto sb;
  }
 else if(bboar>8||bdest>8)
  {
   clrscr();
   header();
   cout<<" Please enter a valid choice!";
   goto sb;
  }
   else if(search(bboar,bdest,3)<0)
  {
   cout<<"\n Sorry route not available!!";
   cout<<"\n<press any key> ";
   char f;
   cin>>f;
   goto a; 
  }

 else if(cfm)
  {
   mode = 3;
   ::start = bboar;
   ::end = bdest;
   reservationdet();
  }
}

//User details input
void reservationdet()
{ 
 header();
sr:int type=0,route=-1;
 char ans;
 route=search(::start,::end,mode);
 id++;
 header();
 pass[id].modec=mode;
 pass[id].startc=::start;
 pass[id].endc=::end;
 cout<<"\n\nPlease enter the following details!";
 cout<<"\n \n\nPassenger name : ";
 cin>>pass[id].name;
vb:cout<<\nPassenger age :";
 cin>>pass[id].age;
 if(pass[id].age>120)
 { 
  cout<<"\nYou seem a bit too old to travel , please reconsider ";
  char ee;
  cout<<"\n<Press any key>";
  cin>>ee;
  home();
 }
 if(pass[id].age<0)
 {
  cout<<"\nPlease enter the right age!";
  goto vb;
 }
 
 if (mode==1)
 cout<<"\nClass (1-first , 2-Economy):";
 else if(mode==2)
 cout<<"\nClass (1-A/C ,2-Sleeper):";
 else if(mode==3)
 cout<<"\nClass (1-Express,2-Normal):";
 cin>>type;
d:cout<<"\nDate :";
 cin>>pass[id].date;
m:cout<<"\nMonth(no) :";
 cin>>pass[id].month;
 if(pass[id].month>12)
  {
   cout<<"\nRe enter month!" ;
   goto m;
  }
f:if(pass[id].date>31)
  {
   cout<<"\nRe enter date!";
   goto d;
  }
 int v=pass[id].month;
 int q=pass[id].date;

 if(v==2&&q>=29)
  goto f;
 if(v==4||v==6||v==9||v==11)
  if(q>=30)
   goto f;

 pass[id].type=type;
 if(mode==1) //flight
 {  
   if (pass[id].age <=12 || pass[id].age>60)
     { 
       cout<<"\n Total amount:RS.";
       if(type==1)
	  {
	   cout<<fl[route].cffprice;
	   pass[id].billamt=fl[route].cffprice;
	  }

	else if (type==2)
	  {
	   cout<<fl[route].cfeprice;
	   pass[id].billamt=fl[route].cfeprice;
	  }
      }


     else
     {     
       cout<<"\n Total amount:RS.";
       if(type==1)
	  {
	   cout<<fl[route].affprice;
	   pass[id].billamt=fl[route].affprice;
	  }
	else if (type==2)
	  {
	   cout<<fl[route].afeprice;
	   pass[id].billamt=fl[route].afeprice;
	  }
      }
 }

  if(mode==2)//Train
 {  
   if (pass[id].age <=12 || pass[id].age>60)
    {
        cout<<"\n Total amount:RS.";
	if(type==1)
	{
          cout<<t[route].tdist;
	  pass[id].billamt=t[route].tdist;
	}
	
         else if (type==2)
	{ 
          cout<<t[route].tdist*0.2;
	  pass[id].billamt=t[route].tdist*0.2;
	}
    }

    else
    { 
        cout<<"\n Total amount:RS.";
        if(type==1)
	 {
          cout<<t[route].tdist*1.3;
	   pass[id].billamt=t[route].tdist*1.3;
	  }
	 
        else if (type==2)
	  {
           cout<<t[route].tdist*0.3;
	   pass[id].billamt=t[route].tdist*0.3;
        }

    }
 }

 if(mode==3) //bus
 {  
   if (pass[id].age <=12 || pass[id].age>60)
     { 
        cout<<"\n Total amount:RS.";
	if(type==1)
	  {
	   cout<<bus[route].cbfprice;
	   pass[id].billamt=bus[route].cbfprice;
	  }
	else if (type==2)
	  {
	   cout<<bus[route].cbeprice;
	   pass[id].billamt=bus[route].cbeprice;
	  }
     }


    else //bus adult
       { 
         cout<<"\n Total amount:RS.";
         if(type==1)
	   {
	    cout<<bus[route].abfprice;
	    pass[id].billamt=bus[route].abfprice;

	   }
         else if (type==2)
	   {
	    cout<<bus[route].abeprice;
	    pass[id].billamt=bus[route].abeprice;
           }
       }
 }

c:cout<<"\nEnter Credit card no:";
 pass[id].ct=1; //Avoiding runtime errors
 cin>>pass[id].ccno;
 cout<<"\nType:\n1)Visa \n2)Mastercard \n3)Cirrus \n4)American Express\n";
 cin>>pass[id].ct;
 if(pass[id].ct>4||pass[id].ct<1)
 {
  cout<<"\nEnter right choice";
  goto c;
 }
 pass[id].route=route;
int cfm;
ts:cout<<"\n\n Confirm?(1-yes/0-no)"; 
 cin>>cfm;
 if(cfm)
 billing(id);
 else if (!cfm)
 {
  id--;
  goto sr;
 }
 else
 {
  cout<<"\nEnter the right choice!";
  goto ts;
 }

}

 //Bill
void billing(int id)
{ 
 header();
 cout<<"\nPassenger Details:\n\n\n";
 cout<<"\n\n PNR :"<<pass[id].id;
 cout<<"\n\n Name:";puts(pass[id].name);
 cout<<"\n\n From:";
 town(pass[id].startc);
 cout<<"\n\n To  :"  ;
 town(pass[id].endc);
  if (mode==1)
  cout<<"\n\n Flight no:"<<fl[pass[id].route].flno;

  if (mode==2)
  cout<<"\n\n Train no:"<<t[pass[id].route].tno;

  if (mode==3)
  cout<<"\n\n Bus no:"<<bus[pass[id].route].bno;

 cout<<"\n\n Dept. on :"<<pass[id].date<<"-"<<pass[id].month<<"-14";
  if (mode==1)
  cout<<"\n\n Dept. Time:"<<(fl[pass[id].route].fdept)%3000<<"hrs";

  if (mode==2)
  cout<<"\n\n Dept. Time:"<<(t[pass[id].route].tdept)%3000<<"hrs";
  
  if (mode==3)
  cout<<"\n\n Dept. Time:"<<(bus[pass[id].route].bdept)%3000<<"hrs";

 cout<<"\n\n Seat No:";
  if(mode==1)
  {
   if(pass[id].type==1)
    { 
      cout<<fl[pass[id].route].fseatsavlf;
      fl[pass[id].route].fseatsavlf--; //reduction in no of seats avl
    }

   if(pass[id].type==2)
    { 
      cout<<fl[pass[id].route].fseatsavle;
      fl[pass[id].route].fseatsavle--;
    }
  }

  if(mode==2)
  { 
   if(pass[id].type==1)

    { 
      cout<<t[pass[id].route].tseatsavlf;
      t[pass[id].route].tseatsavlf--;
    }
   if(pass[id].type==2)
    { 
      cout<<t[pass[id].route].tseatsavle;
      t[pass[id].route].tseatsavle--;
    }
  }

  if(mode==3)
   { 
    if(pass[id].type==1)

    { 
      cout<<bus[pass[id].route].bseatsavlf;
      bus[pass[id].route].bseatsavlf--;
    }
  
    if(pass[id].type==2)
    { 
      cout<<bus[pass[id].route].bseatsavle;
      bus[pass[id].route].bseatsavle--;
    }
 }
 int cfm;
 cout<<"\n\n\n\t\t Thankyou for choosing us , wish you a Happy Journey!";
dh:cout<<"\n\n\nReturn to home page?(1-yes/0-no)";
 cin>>cfm;
 if(cfm)
 { 
  clrscr();
  home(); 
 }
 else if (!cfm)
 {
 cout<<"\Do book with us again!";
 }
 else
 {
  cout<<"\nEnter the right choice!";
  goto dh;
 }

}



void main()
{
 home();
 getch();
}








