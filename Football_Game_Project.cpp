
/*This Project Includes Mentioned Features:

1-Time Management
2-Colored-Texts
3-Sound-Production
*/

/*----INSTRUCTION----

-to create a player, print(new player name price speed finishing defence)

-to create a team, print(new team name money)

-to buy a player, print(buy playerID teamID)

-to sell a player, print(sell playerID teamID)

-to play a friendlyMatch, print(friendlyMatch teamID1 teamID2)

-to play a Match, print(Match teamID1 teamID2)

-to begin a league, print(BeginLeague)

*/


//Terminal Color Codes
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
//++++++++++++++++++++++++++++++++++++++++++
//Headers
//++++++++++++++++++++++++++++++++++++++++++
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <ctime>
#include <windows.h>


using namespace std;


//++++++++++++++++++++++++++++++++++++++++++
//STRUCTURES
//++++++++++++++++++++++++++++++++++++++++++
const int n=300;
//Player Structure
struct Player
{
    int ID;
    string name;
    int price;
    int speed;
    int finishing;
    int defence;
    int strength=speed+finishing+defence;
    string position;
}player[n];

//Team Structure
struct Team
{
    int ID;
    string name;
    int money;
    int players[11]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int strength;//normal strength
    int Match_Strength=0;//weather affected strength
    int GF;//goals for
    int GA;//goals against
    int GD;
    bool fullPlayer=false;
    int wins;
    int draws;
    int loses;
    int points;
}team[n];

struct League
{
    int teams[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
}league;

//++++++++++++++++++++++++++++++++++++++++++
//Prototype Functions
//++++++++++++++++++++++++++++++++++++++++++

int DO();
void newPlayer(int);
int newTeam(int);
void buyPlayer();
void sellPlayer();
void friendlyMatch();
int teamStrength(int);
void Match(int ,int );
int Match_teamStrength(int teamID,int weatherInfo);
int weather();
string Player_Position(int playerID);
int Goal_Numbers();
void teamInfo(int teamID);
string weatherInfo(int weather);
void League();
int team1(int teamID);
int team2(int teamID);
void sleep(unsigned milliseconds);
int Random(int Min, int Max);



//++++++++++++++++++++++++++++++++++++++++++
//Main Function
//++++++++++++++++++++++++++++++++++++++++++
int main()
{
    system("cls");
    DO();
    return 0;

}

//++++++++++++++++++++++++++++++++++++++++++
//functions
//++++++++++++++++++++++++++++++++++++++++++
int DO()
{
    int Frst_team,Sec_team;
    int i=1;
    int j=1;
    int a=0;
    string str1,str2;
    while(str1!="end")
    {
        cin>>str1;
        if(str1=="new")
        {
            cin>>str2;
            if(str2=="player")//New Player
            {
                player[i].ID=i;
                newPlayer(i);
                    i++;
            }
            else if(str2=="team")//New Team
            {
                team[j].ID=j;
                if(newTeam(j)==1)
                    j++;
                else
                    continue;
            }
        }
        else if(str1=="buy")
                buyPlayer();
        else if(str1=="friendlyMatch")
            friendlyMatch();
        else if(str1=="sell")
            sellPlayer();
        else if(str1=="Match")
        {
            Frst_team=team1(Frst_team);
            Sec_team=team2(Sec_team);
            Match(Frst_team,Sec_team);
        }
        else if(str1=="BeginLeague")
            League();
    }
    return 0;
}
//Create New Player
void newPlayer(int j)
{
    cin>>player[j].name>>player[j].price>>player[j].speed>>player[j].finishing>>player[j].defence;
    player[j].position=Player_Position(j);
}

//Create New Team
int newTeam(int j)
{
    int flag=1;
    cin>>team[j].name>>team[j].money;
    for(int i=0;i<j;i++)
    {
        if(team[i].name==team[j].name)
            flag=0;
    }
    if(flag==1)
    {
        return 1;
    }
    else
        return 2;
}


//Buy Players
void buyPlayer()
{
    int flag=1;
    int playerID, teamID,ID;
    cin>>playerID>>teamID;
    for(int i=0;i<11;i++)
    {
        if(team[teamID].players[i]==-1)
        {
            ID=i;
            flag=0;
            break;
        }
    }
    if(player[playerID].ID!=playerID)
        cout<<RED<<"player with the id playerID doesnt exist"<<RESET<<endl;
    else if(team[teamID].ID!=teamID)
        cout<<RED<<"team with the id teamID doesnt exist"<<RESET<<endl;
    else if(team[teamID].money<player[playerID].price)
        cout<<RED<<"the team cant afford to buy this player"<<RESET<<endl;
    else if(flag==1)
        cout<<RED<<"team is full"<<RESET<<endl;
    else
    {
        printf("player %d added to the team %d successfully\n",player[playerID].ID,team[teamID].ID);
        team[teamID].money-=player[playerID].price;
        team[teamID].players[ID]=player[playerID].ID;

    }
}
//Sell Player
void sellPlayer()
{
    int playerID, teamID,ID,flag=1;
    cin>>playerID>>teamID;
    for(int i=0;i<11;i++)
    {
        if(team[teamID].players[i]==playerID)
        {
            flag=0;
            ID=i;
        }
    }
    if(player[playerID].ID!=playerID)
        cout<<RED<<"player with the id playerID doesnt exist"<<RESET<<endl;
    else if(team[teamID].ID!=teamID)
        cout<<RED<<"team with the id teamID doesnt exist"<<RESET<<endl;
    else
    {
        printf("player %d removed from the team %d successfully\n",player[playerID].ID,team[teamID].ID);
        team[teamID].money+=player[playerID].price;
        for(int j=ID;j<11;j++)
            {
                team[teamID].players[j]=team[teamID].players[j+1];
            }
        team[teamID].players[10]=-1;
    }
}
//Friendly Match
void friendlyMatch()
{
    int teamID1, teamID2;
    cin>>teamID1>>teamID2;
    if(team[teamID1].ID!=teamID1)
        cout<<RED<<"team doesnt exist"<<RESET<<endl;
    else if(team[teamID2].ID!=teamID2)
        cout<<RED<<"team doesnt exist"<<RESET<<endl;
    else if(team[teamID1].players[10]==-1 || team[teamID2].players[10]==-1)
        cout<<RED<<"the game can not be held due to loss of the players"<<RESET<<endl;
    else if(teamStrength(teamID1)>teamStrength(teamID2))
        printf("team %d win\n",teamID1);
    else if(teamStrength(teamID2)>teamStrength(teamID1))
        printf("team %d win\n",teamID2);
    else
        printf("the match is draw\n");
}
//Return Strength of a team
int teamStrength(int teamID)
{
    for(int i=1;i<11;i++)
    {
        team[teamID].strength+=player[team[teamID].players[i]].speed+player[team[teamID].players[i]].finishing+player[team[teamID].players[i]].defence;
    }
    return team[teamID].strength;
}
//Player Position
string Player_Position(int playerID)
{
    string position;
    int max1=max(player[playerID].speed,player[playerID].finishing);
    int max2=max(max1,player[playerID].defence);
    if(player[playerID].speed==player[playerID].defence || player[playerID].defence==player[playerID].finishing)
        position= "normal";
    else if(max2==player[playerID].speed)
        position= "halfBack";
    else if(max2==player[playerID].finishing)
        position= "stricker";
    else if(max2==player[playerID].defence)
        position= "defender";
    return position;

}
//Weather Generator
int weather()
{
    string weather;
    srand(time(0));  // Initialize random number generator.
    int randomNumber=(rand() % 4) + 1;
    if(randomNumber==1)
    {
        weather="sunny";
        return 1;
    }

    else if(randomNumber==2)
    {
        weather="rainy";
        return 2;
    }
    else if(randomNumber==3)
    {
        weather="snowy";
        return 3;
    }
    else
    {
        weather="cloudy";
        return 4;
    }
}
//Calculate match team strength
int Match_teamStrength(int teamID,int weatherInfo)
{
    for(int i=1;i<11;i++)
    {
        if(weatherInfo==1 && player[team[teamID].players[i]].position=="defender")
            team[teamID].Match_Strength+=player[team[teamID].players[i]].speed+player[team[teamID].players[i]].finishing-player[team[teamID].players[i]].defence;
        else if(weatherInfo==2 && player[team[teamID].players[i]].position=="halfBack")
            team[teamID].Match_Strength+=(player[team[teamID].players[i]].speed/2)+player[team[teamID].players[i]].finishing+player[team[teamID].players[i]].defence;
        else if(weatherInfo==3 && player[team[teamID].players[i]].position=="stricker")
            team[teamID].Match_Strength+=player[team[teamID].players[i]].speed+player[team[teamID].players[i]].finishing-player[team[teamID].players[i]].defence-10;
        else
            team[teamID].Match_Strength+=player[team[teamID].players[i]].speed+player[team[teamID].players[i]].finishing-player[team[teamID].players[i]].defence;
    }
    return team[teamID].Match_Strength;
}

int team1(int teamID1)
{
    int userIn;
    cin>>userIn;
    return userIn;
}
int team2(int teamID2)
{
    int userIn;
    cin>>userIn;
    return userIn;
}
//Match Function
void Match(int teamID1,int teamID2)
{
    sleep(1500);
    int Weather=weather();

    int goals1,goals2;

    if(team[teamID1].ID!=teamID1)
        cout<<RED<<"team doesnt exist"<<RESET<<endl;
    else if(team[teamID2].ID!=teamID2)
        cout<<RED<<"team doesnt exist"<<RESET<<endl;
    else if(team[teamID1].players[10]==-1 || team[teamID2].players[10]==-1)
        cout<<RED<<"the game can not be held due to loss of the players"<<RESET<<endl;
    else
    {

        if(Match_teamStrength(teamID1,Weather)>Match_teamStrength(teamID2,Weather))
            {
                teamInfo(teamID1);
                teamInfo(teamID2);

                cout<<"Weather Type : "<<weatherInfo(Weather)<<endl;
                goals1=Goal_Numbers();
                goals2=Goal_Numbers()%goals1;
                team[teamID1].GF+=goals1;
                team[teamID2].GF+=goals2;
                team[teamID1].GA+=goals2;
                team[teamID2].GA+=goals1;
                team[teamID1].wins++;
                team[teamID2].loses++;
                ;printf("Team %s win With %d Goal(s)!\n",(team[teamID1].name).c_str(),goals1);
                cout<<goals1<<" : "<<goals2<<endl;
            }
            else if(Match_teamStrength(teamID2,Weather)>Match_teamStrength(teamID1,Weather))
            {
                teamInfo(teamID1);
                teamInfo(teamID2);

                cout<<"Weather Type : "<<weatherInfo(Weather)<<endl;
                goals2=Goal_Numbers();
                goals1=Goal_Numbers()%goals2;
                team[teamID1].GF+=goals1;
                team[teamID2].GF+=goals2;
                team[teamID1].GA+=goals2;
                team[teamID2].GA+=goals1;
                team[teamID2].wins++;
                team[teamID1].loses++;
                printf("Team %s win With %d Goal(s)!\n",(team[teamID2].name).c_str(),goals2);
                cout<<goals1<<" : "<<goals2<<endl;
            }
            else
            {
                teamInfo(teamID1);
                teamInfo(teamID2);
                cout<<"Weather Type : "<<weatherInfo(Weather)<<endl;
                printf("draw\n");
                goals1=Goal_Numbers();
                goals2=goals1;
                team[teamID1].GF+=goals1;
                team[teamID2].GF+=goals2;
                team[teamID1].GA+=goals2;
                team[teamID2].GA+=goals1;
                team[teamID1].draws++;
                team[teamID2].draws++;
                cout<<goals1<<" : "<<goals2<<endl;
            }
            team[teamID1].points=team[teamID1].wins*3+team[teamID1].draws;
            team[teamID2].points=team[teamID2].wins*3+team[teamID2].draws;
            team[teamID2].GD=team[teamID2].GF-team[teamID2].GA;
            team[teamID1].GD=team[teamID1].GF-team[teamID1].GA;
    }
}
//Goal Generator
int Goal_Numbers()
{
    int randomNumber=Random(1,100);
    if(randomNumber<=50)
        return 1;
    else if(randomNumber>50 && randomNumber<=80)
        return 2;
    else if(randomNumber>80 && randomNumber<=95)
        return 3;
    else
        return (rand()%10)+4;
}
//Information of a Team
void teamInfo(int teamID)
{

    cout<<"---------Team ( "<<team[teamID].name<<" ) Players---------";
    for(int i=0;i<11;i++)
    {
        cout<<"{"<<player[team[teamID].players[i]].name<<" : "<<player[team[teamID].players[i]].position<<"} ";
    }cout<<endl;
}
//Show Chosen weather
string weatherInfo(int weather)
{
    if(weather==1)
        return "snowy";
    else if(weather==2)
        return "rainy";
    else if(weather==3)
        return "sunny";
    else
        return "cloudy";
}
int Number_of_teams()//Calculate number of Accepted teams
{

    int teamNums=0;
    for(int i=1;i<n;i++)
    {
        if(team[i].players[10]!=-1)
        {
            teamNums++;
            team[i].fullPlayer=true;//league Condition #1
        }

    }return teamNums;
}

void league_Insert(int teamNums)//Insert teams to League Array
{
        for(int j=1;j<=teamNums;j++)
        {
            if(team[j].fullPlayer==true)//Reset Goal Settings for league
            {
                league.teams[j-1]=team[j].ID;
                team[league.teams[j-1]].GA=0;
                team[league.teams[j-1]].GF=0;
                team[league.teams[j-1]].GD=0;
                team[league.teams[j-1]].wins=0;
                team[league.teams[j-1]].loses=0;
                team[league.teams[j-1]].draws=0;
                team[league.teams[j-1]].points=0;
            }
            else
                continue;
        }

}
int breakPoint()//Return the Stop of League array
{
    int flag;
    for(int i=0;i<10;i++)
    {
        if(league.teams[i]==-1)
        {
            flag=i;
            break;
        }
        else
            flag= 10;
    }
    return flag;
}


void League()//Begin a League
{
    int teamNums=Number_of_teams();//Number of teams
    league_Insert(teamNums);//Prepare for League
    int Stop=breakPoint();

    for(int i=0;i<Stop;i++)//Weekly Match Generator
    {
        for(int j=i+1;j<Stop;j++)
            {
                int freq[5]={500,500,0,500,500},dur[5]={500,500,1000,500,500};
                Beep(freq[i],dur[i]);
                Match(league.teams[i],league.teams[j]);

            }
    }
    for (int i = Stop; i >= 0; i--)//descending Order By Team Point
        for (int j = Stop; j > Stop-i; j--)
        {
            if (team[league.teams[j]].points > team[league.teams[j-1]].points)
            {
                int temp = league.teams[j];
                if(team[league.teams[j]].points == team[league.teams[j-1]].points)//Equal Points Condition
                {
                    if(team[league.teams[j]].GD > team[league.teams[j-1]].GD)
                    league.teams[j] = league.teams[j-1];
                    league.teams[j-1] = temp;
                }else
                {

                    league.teams[j] = league.teams[j-1];
                    league.teams[j-1] = temp;
                }

            }
        }
	cout << left;//Draw League Table
	cout <<BOLDGREEN<<
	    setw(6) << "[RANK] " << setw(11) << "[TEAM]      " << setw(9) << "[POINTS] " <<setw(7) << "[GF] "<<setw(6) << "[GA] "
	     <<setw(6) << "[GD] "<<setw(8) << "[WINS] "<<setw(4) << "[LOSSES] "<<setw(4) << "[DRAWS]"<<'\n' <<
        "__________________________________________________________________________"<< RESET<<endl;
        for(int i=0;i<Stop;i++)
            {
                cout << left;
                cout <<BOLDBLUE<<setw(8)<<i+1<< setw(12)<<team[league.teams[i]].name<<setw(8)<<team[league.teams[i]].points<<setw(7) <<team[league.teams[i]].GF<<
                setw(6) <<team[league.teams[i]].GA<<setw(8) <<team[league.teams[i]].GD
                <<setw(9) <<team[league.teams[i]].wins<<setw(9) <<team[league.teams[i]].loses<<setw(4) <<team[league.teams[i]].draws<<RESET<<'\n';
                int freq[7]={500,500,600,500,500,700,700},dur[7]={500,500,1000,500,500,500,500};
                for(int i=0;i<7;i++)
                    Beep(freq[i],dur[i]);
            }
}
void sleep(unsigned milliseconds)//Run Program Slower
{
    Sleep(milliseconds);
}
int Random(int Min,int Max)//Generate Random Number
{
    static int RunCount=0;
    RunCount++;
    if(RunCount==1)
        srand(time(0));
    Max++;
    double val=1.0*rand()/RAND_MAX;
    int result=val*(Max-Min)+Min;
    return result;
}


