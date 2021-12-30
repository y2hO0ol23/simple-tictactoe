#include <stdio.h>
#include <stdlib.h> // system("cls"); 사용을 위한 해더파일

int lobby();
void draw_lobby(int select);
void draw_game(int y, int x);
int press(int y, int x);
int who_win();
void draw_end(int win);

int field[3][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
int turn = 0;
int turn_cnt = 0;

char table[4] = { ' ', 'X', 'O', 'V' };

int main() {
	int select = lobby();
	if (select == 1) return 0;

	int x = 1, y = 1;
	int win = 0;
	draw_game(y, x);
	while(1) {
		if (!kbhit()) continue;

		int key = getch();
		if (key == 's' && y < 2) y += 1;
		if (key == 'w' && y > 0) y -= 1;
		if (key == 'd' && x < 2) x += 1;
		if (key == 'a' && x > 0) x -= 1;
		if (key == ' ') win = press(y, x);

		if (win) break;
		draw_game(y, x);
	}
	draw_end(win);
	while (!kbhit());
}

int lobby() {
	int select = 0;
	draw_lobby(select);
	while(1) {
		if (!kbhit()) continue;

		int key = getch();
		if (key == 'w') select -= 1;
		if (key == 's') select += 1;
		if (key == ' ') break;

		select = (select + 2) % 2;
		draw_lobby(select);
	}
	return select;
}

void draw_lobby(int select) {
	system("cls");
	printf("┌────────────────────┐\n");
	printf("│      tictactoe     │\n");
	printf("└────────────────────┘\n");
	printf("\n");
	printf("       %c start\n",(select == 0) ? '-' : ' ');
	printf("       %c exit\n", (select == 1) ? '-' : ' ');
}

void draw_game(int y, int x) {
	system("cls");
	char output[3][3][3] = {
		{"─","─","─"},
		{"─","─","─"},
		{"─","─","─"}
	};
	output[y][x][0] = 'V';
	output[y][x][1] = '\0';
	  printf("┌─%s┬─%s┬─%s┐", output[0][0], output[0][1], output[0][2]); printf("\t% c turn\n", (turn == 0)  ? 'X' : 'O');
	  printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[0][i]]);

	printf("\n├─%s┼─%s┼─%s┤\n", output[1][0], output[1][1], output[1][2]);
	  printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[1][i]]);

	printf("\n├─%s┼─%s┼─%s┤\n", output[2][0], output[2][1], output[2][2]);
	  printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[2][i]]);
	printf("\n└──┴──┴──┘");
}

int press(int y, int x) {
	if (field[y][x] != 0) return 0;
	field[y][x] = 1 + turn;
	turn = (turn + 1) % 2;
	turn_cnt++;
	
	int w = who_win();
	if (w) return w;
	if (turn_cnt == 9) return 3;
	return 0;
}

int who_win() {
	for (int i = 0; i < 3; i++) {
		if (field[i][0] == 0) continue;
		int is_same = 1;
		for (int j = 1; j < 3; j++)
			if (field[i][0] != field[i][j]) is_same = 0;

		if (is_same) return field[i][0];
	}
	for (int i = 0; i < 3; i++) {
		if (field[0][i] == 0) continue;
		int is_same = 1;
		for (int j = 1; j < 3; j++)
			if (field[0][i] != field[j][i]) is_same = 0;

		if (is_same) return field[0][i];
	}
	if (field[0][0] != 0) {
		int is_same = 1;
		for (int i=0;i<3;i++)
			if (field[0][0] != field[i][i]) is_same = 0;

		if (is_same) return field[0][0];
	}
	if (field[0][2] != 0) {
		int is_same = 1;
		for (int i = 1; i < 3; i++)
			if (field[0][0] != field[i][2-i]) is_same = 0;

		if (is_same) return field[0][2];
	}
	return 0;
}

void draw_end(int win) {
	system("cls");
	if (win == 1) printf("X win!");
	if (win == 2) printf("O win!");
	if (win == 3) printf("draw!");
	printf("\n\npress any key to exit program...");
}
