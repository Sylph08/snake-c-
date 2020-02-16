#include <iostream>
#include "kmin_console.h"
#include <conio.h>
#include <windows.h>
#include <vector>
#include <time.h>
#define TRAI_X 10
#define PHAI_X 80
#define TRAI_Y 5
#define PHAI_Y 20
#define Snake_Speed 150
#define DOT_RAN 233
using namespace std;
struct vitri
{
	int hd;
	int td;
};

static int Snalen = 3;
static vector<vitri> snake(Snalen);
static vitri cur_position{ (int)(TRAI_X / 2 + PHAI_X / 2),(int)(TRAI_Y / 2 + PHAI_Y / 2) };
static char huong_htai = 'r';
static vitri vitri_cuoi;
static vitri moi;

//xac dinh huong di hien tai cua ran
//char define_Sna_direct(vitri &v1, vitri &v0)
//{
//	//huong trai, phai
//	if (v1.td == v0.td)
//	{
//		if (v1.hd < v0.hd) return 'r';
//		else return 'l';
//	}
//	if (v1.hd == v0.hd)
//	{
//		if (v1.td < v0.td) return 'd';
//		else return 'u';
//	}
//}
//quy luat cua ran
void Snake_rule(vector<vitri> &temp, vitri t0_moi){
	vitri_cuoi = temp[Snalen - 1];
	for (int i = Snalen - 1;i > 0;i--) {
		temp[i] = temp[i - 1];
	}
	temp[0] = t0_moi;
}
//chuyen cur_position sang huong trai 
void turn_left(vitri i0){
	if (huong_htai == 'r') {
		cur_position.hd = i0.hd;
		cur_position.td = i0.td-1;		
	}
	if (huong_htai == 'l') {
		cur_position.hd = i0.hd;
		cur_position.td = i0.td+1;
	}
	if (huong_htai == 'u') {
		cur_position.hd = i0.hd-1;
		cur_position.td = i0.td;
	}
	if (huong_htai == 'd') {
		cur_position.hd = i0.hd+1;
		cur_position.td = i0.td;
	}
}
//chuyen cur_position sang huong phai
void turn_right(vitri i0){
	if (huong_htai == 'r') {
		cur_position.hd = i0.hd;
		cur_position.td = i0.td + 1;
	}
	if (huong_htai == 'l') {
		cur_position.hd = i0.hd;
		cur_position.td = i0.td - 1;
	}
	if (huong_htai == 'u') {
		cur_position.hd = i0.hd + 1;
		cur_position.td = i0.td;
	}
	if (huong_htai == 'd') {
		cur_position.hd = i0.hd - 1;
		cur_position.td = i0.td;
	}
}
//in ran
//void print_snake(vector<vitri> temp, int leng) {	
//		for (int i = 0;i < leng;i++) {
//			gotoXY(temp[i].hd, temp[i].td);
//			cout << (char)DOT_RAN;
//		}	
//}
void xoa_vi_tri_cuoi(vitri v1)
{
	gotoXY(v1.hd, v1.td);
	cout << " ";
}
//ran di thang
void ran_di_thang(vitri i0)
{
	if (huong_htai == 'r') {
		cur_position.hd = i0.hd + 1;
		cur_position.td = i0.td;
	}
	if (huong_htai == 'l') {
		cur_position.hd = cur_position.hd - 1;
		cur_position.td = i0.td;
	}
	if (huong_htai == 'u') {
		cur_position.td = cur_position.td - 1;
		cur_position.hd = cur_position.hd;
	}
	if (huong_htai == 'd') {
		cur_position.td = cur_position.td + 1;
		cur_position.hd = cur_position.hd;
	}
}
//ve tuong
void Wall()
{
	for (int i = TRAI_X;i < PHAI_X;i++) {
		gotoXY(i, TRAI_Y);
		cout << (char)220;
		gotoXY(i, PHAI_Y);
		cout << (char)223;
	}
	for (int i = TRAI_Y+1;i < PHAI_Y;i++) {
		gotoXY(TRAI_X,i);
		cout << (char)221;
		gotoXY(PHAI_X-1, i);
		cout << (char)222;
	}
}
//ham sinh moi
void sinh_moi()
{
cp1:
	srand((int)time(NULL));
	moi.hd = TRAI_X+1 + rand() % (PHAI_X - 2 - TRAI_X);
	moi.td = TRAI_Y+1 + rand() % (PHAI_Y - 2 - TRAI_Y);
	for (int i = 0;i < Snalen;i++)
	{
		if (moi.hd == snake[i].hd) {
			if (moi.td == snake[i].td) goto cp1;
		}
		else continue;
	}	
	gotoXY(moi.hd, moi.td);
	cout << (char)153;
}
//xu ly cham moi
void tourch_moi()
{
	//dk cham moi:cur_position co toa do trung vs moi
	if (snake[0].hd==moi.hd&&snake[0].td==moi.td)
	{
	//ran dai them
		Snalen++;
		snake.push_back(vitri_cuoi);
		sinh_moi();		
	}
}
//xu ly va cham ket thuc game
void end_game()
{
	cout << "\a";
	gotoXY(snake[0].hd, snake[0].td);
	setTextColor(12);
	cout << 'X';
	Sleep(2000);
}

void Sna_Move(){
	int huong_re;
	int dem=0;
	Wall();
	sinh_moi();
	while (true)
	{				
		//in vi tri dau
		gotoXY(snake[0].hd, snake[0].td);
		cout << (char)DOT_RAN;
		//xoa cuoi
		xoa_vi_tri_cuoi(vitri_cuoi);
		tourch_moi();
		huong_re = inputKey();
		if (huong_htai == 'r') {			
			//re trai
			if (huong_re == KEY_UP) {
					turn_left(snake[0]);
					huong_htai = 'u';
			}
			//re phai
			if (huong_re == KEY_DOWN) {
					turn_right(snake[0]);
					huong_htai = 'd';
			}
			if (huong_re == KEY_NONE || huong_re == KEY_RIGHT||huong_re==KEY_LEFT) {
					ran_di_thang(snake[0]);
			}
		}
		if (huong_htai == 'l') {
			//re trai
			if (huong_re == KEY_DOWN) {
				turn_left(snake[0]);
				huong_htai = 'd';
			}
			//re phai
			if (huong_re == KEY_UP) {
				turn_right(snake[0]);
				huong_htai = 'u';
			}
			if (huong_re == KEY_NONE || huong_re == KEY_LEFT||huong_re==KEY_RIGHT) {
				ran_di_thang(snake[0]);
			}
		}
		if (huong_htai == 'u') {
			//re trai
			if (huong_re == KEY_LEFT) {
				turn_left(snake[0]);
				huong_htai = 'l';
			}
			//re phai
			if (huong_re == KEY_RIGHT) {
				turn_right(snake[0]);
				huong_htai = 'r';
			}
			if (huong_re == KEY_NONE || huong_re == KEY_UP||huong_re==KEY_DOWN) {
				ran_di_thang(snake[0]);
			}
		}
		if (huong_htai == 'd') {
			//re trai
			if (huong_re == KEY_RIGHT) {
				turn_left(snake[0]);
				huong_htai = 'r';
			}
			//re phai
			if (huong_re == KEY_LEFT) {
				turn_right(snake[0]);
				huong_htai = 'l';
			}
			if (huong_re == KEY_NONE || huong_re == KEY_DOWN||huong_re==KEY_UP) {
				ran_di_thang(snake[0]);
			}			
		}
		Snake_rule(snake, cur_position);
		//cham tuong
		if (snake[0].td == TRAI_Y || snake[0].td == PHAI_Y || snake[0].hd == TRAI_X || snake[0].hd == PHAI_X)
		{
			end_game();
			break;
		}
		//cham than ran
		for (int i = 1;i < Snalen;i++)
		{
			if (snake[0].hd == snake[i].hd&&snake[0].td == snake[i].td) {
				dem++;
				break;
			}
		}
		if (dem > 0) {
			end_game();
			break;
		}	
		Sleep(Snake_Speed);		
	}
	clrscr();
	gotoXY((int)(TRAI_X / 2 + PHAI_X / 2), (int)(TRAI_Y / 2 + PHAI_Y / 2));
	setTextColor(2);
	cout << "GAME OVER!" << endl;
}

int main() {
	snake[0] = { (int)(TRAI_X / 2 + PHAI_X / 2),(int)(TRAI_Y / 2 + PHAI_Y / 2) };
	snake[1] = { snake[0].hd - 1,snake[0].td };
	snake[2] = { snake[1].hd - 1,snake[1].td };
	noCursorType();	
	Sna_Move();	
	/*for (int i = 0;i < 256;i++)
	{
		cout << i<<": "<<(char)i << endl;
	}*/
	system("pause");
	return 0;
}