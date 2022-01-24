#include <iostream>
using namespace std; 
int count=0;  
int evaluateShape(int chain[5],int team){
	if(chain[0]==team&&chain[1]==team&&chain[2]==team&&chain[3]==team&&chain[4]==0)return 300000;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team&&chain[3]==team)return 150000;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team&&chain[3]==team&&chain[4]==team%2+1)return 2500;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team&&chain[3]==0)return 3000;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team)return 700;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team&&chain[3]==team%2+1)return 500;
	if(chain[0]==team&&chain[1]==team&&chain[2]==0)return 500;
	if(chain[0]==team&&chain[1]==team)return 200;
	if(chain[0]==team&&chain[1]==team&&chain[2]==team%2+1)return 100;
	if(chain[0]==team&&chain[1]==0)return 100;
	if(chain[0]==team&&chain[1]==team%2+1)return 40;
	if(chain[0]==team)return 25;
}
int getValue(int board[15][15],int i,int j,int team){
	int col1[5]={},col2[5]={},row1[5]={},row2[5]={},pdia1[5]={},pdia2[5]={},ndia1[5]={},ndia2[5]={};
	for(int a=1;a<=5;a++){
		if(i+a<=14)col1[a-1]=board[i+a][j];
		if(i-a>=0)col2[a-1]=board[i-a][j];
		if(j+a<=14)row1[a-1]=board[i][j+a];
		if(j-a>=0)row2[a-1]=board[i][j-a];
		if(i+a<=14&&j+a<=14)pdia1[a-1]=board[i+a][j+a];
		if(i-a>=0&&j-a>=0)pdia2[a-1]=board[i-a][j-a];
		if(i+a<=14&&j-a>=0)ndia1[a-1]=board[i+a][j-a];
		if(i-a>=0&&j+a<=14)ndia2[a-1]=board[i-a][j+a];
	}
	int value=0;
	value+=evaluateShape(col1,team);
	value+=evaluateShape(col2,team);
	value+=evaluateShape(row1,team);
	value+=evaluateShape(row2,team);
	value+=evaluateShape(pdia1,team);
	value+=evaluateShape(pdia2,team);
	value+=evaluateShape(ndia1,team);
	value+=evaluateShape(ndia2,team);
	if(i==7&&j==7)value+=1;
	return value;
} 
int getDefValue(int board[15][15],int i,int j,int team){
	return getValue(board,i,j,team)*2;
}
int getAtkValue(int board[15][15],int i,int j,int team){
	return getValue(board,i,j,team);
}
int evaluateBoard(int board[15][15],int team){
	int besti=0,bestj=0,bestval=0,value=0,bestco=0;
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(board[i][j]==0){
				value=0;
				value+=getDefValue(board,i,j,team%2+1);
				value+=getAtkValue(board,i,j,team);
				if(value>bestval){
					bestval=value;
					besti=i;
					bestj=j;
				}
			}
		}
	}
	bestco=besti*100+bestj;
	return bestco;
}
void paintBoard(int board[15][15]){
	for(int i=0;i<15;i++){
		if(15-i<10){
			cout<<15-i<<" ";
		}else{
			cout<<15-i;
		}
		for(int j=0;j<15;j++){
			if(board[i][j]==1){
				if(j==0){
					cout<<"¡ñ©¤";
				}else if(j==14){
					cout<<"©¤¡ñ";
				}else{
					cout<<"©¤¡ñ©¤";
				}
			}else if(board[i][j]==2){
				if(j==0){
					cout<<"¡ğ©¤";
				}else if(j==14){
					cout<<"-¡ğ";
				}else{
					cout<<"-¡ğ©¤";
				}
			}else{
				if(i==0){
					if(j==0){
						cout<<"©°©¤"; 
					}else if(j==14){
						cout<<"©¤©´";
					}else{
						cout<<"©¤©Ğ©¤";
					}
					if(j<14)cout<<"©¤";
				}else if(i==14){
					if(j==0){
						cout<<"©¸©¤"; 
					}else if(j==14){
						cout<<"©¤©¼";
					}else{
						cout<<"©¤©Ø©¤";
					}
					if(j<14)cout<<"©¤";
				}else{
					if(j==0){
						cout<<"©À©¤"; 
					}else if(j==14){
						cout<<"©¤©È";
					}else{
						cout<<"©¤©à©¤";
					}
					if(j<14)cout<<"©¤";
				}
			}
		}
		cout<<endl;
		if(i<14){
			cout<<"  ";
			for(int k=0;k<15;k++){
				cout<<"©¦   ";
			}
			cout<<endl;
		}
	}
	cout<<"   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O";
}
void placing(int board[15][15],int coi,char coj,int team){
	board[15-coi][coj-'A']=team;
}
bool iswin(int board[15][15],int team){
	int crow=0,ccol=0,cpdia=0,cndia=0;
	for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			if(board[i][j]==team){
				crow=0;
				ccol=0;
				cpdia=0;
				cndia=0;
				for(int k=1;k<=4;k++){
					if(j+k<=14&&board[i][j+k]==team)crow++;
					if(i+k<=14&&board[i+k][j]==team)ccol++;
					if(i+k<=14&&j+k<=14&&board[i+k][j+k]==team)cpdia++;
					if(i+k<=14&&j-k>=0&&board[i+k][j-k]==team)cndia++;
				}
				if(crow==4||ccol==4||cpdia==4||cndia==4)return true;
			}
		}
	}
	return false;
}
int main(){
	int board[15][15]={},coi,aico,a;
	char coj;
	paintBoard(board);
	cout<<endl; 
	while(true){
//		cout<<"AI calculating coordinates"<<endl;
//		aico=AI(board,1);
//		coi=15-aico/100;
//		coj=(aico%100)+'A';
//		board[aico/100][aico%100]=1;
		cout<<"please type a coordinate"<<endl;
		cin>>coi>>coj;
		placing(board,coi,coj,1);
		cout<<"white at "<<coi<<coj<<endl;
		count++;
		paintBoard(board);
		cout<<endl;
		if(iswin(board,1)){
			cout<<"white wins";
			break;
		}
		cout<<"AI calculating coordinates"<<endl;
		aico=evaluateBoard(board,2);
		coi=15-aico/100;
		coj=(aico%100)+'A';
		board[aico/100][aico%100]=2;
		paintBoard(board);
		cout<<endl;
//		cout<<"please type a coordinate"<<endl;
//		cin>>coi>>coj;
//		placing(board,coi,coj,2);
//		cout<<"black at "<<coi<<coj<<endl;
//		count++;
//		paintBoard(board);
//		cout<<endl;
		if(iswin(board,2)){
			cout<<"black wins";
			break;
		}
	}
	return 0;
} 
