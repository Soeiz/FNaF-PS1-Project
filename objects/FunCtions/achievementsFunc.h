typedef struct Achievements{
int bronze;
int gold;
int silver;
} Achievements;

Achievements achievements;

void Achievementsthing(){
achievements.bronze = 0;
achievements.gold = 0;
achievements.silver = 0;
}
// Achievement system - START
// Night achievements:
void NightAchievements(int event){
if (event == 1 && night == 1 && nightwon == 1){
for (achievements.bronze = 0; achievements.bronze < 1; achievements.bronze++){}
}//Night 1
if (event == 2 && night == 2 && nightwon == 1){
for (achievements.bronze = 1; achievements.bronze < 2; achievements.bronze++){}
}//Night 2
if (event == 3 && night == 3 && nightwon == 1){
for (achievements.silver = 0; achievements.silver < 1; achievements.silver++){}
}//Night 3
if (event == 4 && night == 4 && nightwon == 1){
for (achievements.silver = 1; achievements.silver < 2; achievements.silver++){}
}//Night 4
if (event == 5 && night == 5 && nightwon == 1){
for (achievements.silver = 2; achievements.silver < 3; achievements.silver++){}
}//Night 5
if (event == 6 && night == 6 && nightwon == 1){
for (achievements.silver = 3; achievements.silver < 4; achievements.silver++){}  
}//Night 6
}
