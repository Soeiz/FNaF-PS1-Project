typedef struct Achievements{
int bronze;
int gold;
int silver;
} Achievements;


void Achievementsthing(){
Achievements.bronze = 0;
Achievements.gold = 0;
Achievements.silver = 0;
}
// Achievement system - START
// Night achievements:
void NightAchievements(int event){
if (event == 1 && night == 1 && nightwon == 1){
for (Achievements.bronze = 0; Achievements.bronze < 1; Achievements.bronze++){}
}//Night 1
if (event == 2 && night == 2 && nightwon == 1){
for (Achievements.bronze = 1; Achievements.bronze < 2; Achievements.bronze++){}
}//Night 2
if (event == 3 && night == 3 && nightwon == 1){
for (Achievements.silver = 0; Achievemnts.silver < 1; Achievements.silver++){}
}//Night 3
if (event == 4 && night == 4 && nightwon == 1){
for (Achievements.silver = 1; Achievements.silver < 2; Achievements.silver++){}
}//Night 4
if (event == 5 && night == 5 && nightwon == 1){
for (Achievements.silver = 2; Achievements.silver < 3; Achievements.silver++){}
}//Night 5
if (event == 6 && night == 6 && nightwon == 1){
for (Achievements.silver = 3; Achievements.silver < 4; Achievements.silver++){}  
}//Night 6
}
