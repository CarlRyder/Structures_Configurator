// Made by Y. Sendov. March 2022

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_NUMS_INPUT 9
#define MAX_DIGIT_INPUT 3
#define MAX_NAMES_LEN 32
#define VEG_MAX_SIZE 8
#define MEAT_MAX_SIZE 8
#define SEAS_MAX_SIZE 5

// ����������� ����� �����������
char sizename[3][10] = {
	"���������", "�������", "�������"
};
char sauce[6][10] = {
	"��������", "��������", "���������", "���������", "���������", "�����"
};
char cheese[4][10] = {
	"���������", "������", "��������", "��������"
};
char meat[7][24] = {
	"�������", "������� �������", "�������", "��������� ���������", "�������", "�����", "������"
};
char seas[3][24] = {
	"����������� �����", "���������� �����", "����������� �����"
};
char vegbig[7][24] = {
	"������� �����", "������� ���", "������ ���������", "������", "������ ��������", "������", "����������"
};
char vegmid[5][24] = {
	"���������", "�������", "�������", "���������� �����", "�������"
};
char vegsmall[3][24] = {
	"������", "������ ���������", "������ ������"
};

// ��������� ��� ���
struct costs
{
	int sizecost[3];
	int saucecost[6];
	int cheesecost[4];
	int vegcost[7];
	int meatcost[7];
	int seascost[3];
}costs;

enum SIZE
{
	SMALL = 1,
	MIDDLE,
	BIG
};

// ��������� ��� �����
struct new_base
{
	int sauce;
	char saucename[MAX_NAMES_LEN];
	int cheese;
	char cheesename[MAX_NAMES_LEN];
};

struct new_fill
{
	int veg[VEG_MAX_SIZE];
	int meat[MEAT_MAX_SIZE];
	int seasonings;
};

struct new_pizza
{
	int size;
	char sizename[MAX_NAMES_LEN];
	struct new_base base;
	struct new_fill fill;
} pizza;

int security(char input[MAX_DIGIT_INPUT])
{
	int flag = 0;
	if (input[0] == '\n') return 1;
	input[strcspn(input, "\n")] = 0;
	for (unsigned int i = 0; i < strlen(input); i++)
	{
		if (input[i] < 48 || input[i] > 57)
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int security_file(char* filename)
{
	int flag = 1;
	FILE* file = fopen(filename, "r");
	// �������� �� ������������� �����
	if (file == NULL) flag = 0;
	else
	{
		// �������� �� ���������� �����
		char str[32];
		for (int i = 1; i < 11; i++)
		{
			fgets(str, sizeof(str), file);
			str[strcspn(str, "\n")] = 0;
			if (i == 1)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 3)) flag = 0;
			}
			else if (i == 2)
			{
				if (strlen(str) > 9 || (strcmp(str, sizename[0]) != 0 && strcmp(str, sizename[1]) != 0 && strcmp(str, sizename[2]) != 0)) flag = 0;
			}
			else if (i == 3)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 6)) flag = 0;
			}
			else if (i == 4)
			{
				if (strlen(str) > 9 || (strcmp(str, sauce[0]) != 0 && strcmp(str, sauce[1]) != 0 && strcmp(str, sauce[2]) != 0 && strcmp(str, sauce[3]) != 0 && strcmp(str, sauce[4]) != 0 && strcmp(str, sauce[5]) != 0)) flag = 0;
			}
			else if (i == 5)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 4)) flag = 0;
			}
			else if (i == 6)
			{
				if (strlen(str) > 9 || (strcmp(str, cheese[0]) != 0 && strcmp(str, cheese[1]) != 0 && strcmp(str, cheese[2]) != 0 && strcmp(str, cheese[3]) != 0)) flag = 0;
			}
			else if (i == 7)
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (strlen(str) > 7)
					{
						flag = 0;
						break;
					}
					if (isdigit(str[j]) == 0 || (isdigit(str[j]) != 0 && (str[j] - '0') > 7)) flag = 0;
				}
			}
			else if (i == 8)
			{
				for (int j = 0; j < strlen(str); j++)
				{
					if (strlen(str) > 7)
					{
						flag = 0;
						break;
					}
					if (isdigit(str[j]) == 0 || (isdigit(str[j]) != 0 && (str[j] - '0') > 7)) flag = 0;
				}
			}
			else if (i == 9)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 3)) flag = 0;
			}
			else if (i == 10)
			{
				if (str[0] != 0) flag = 0;
			}
			memset(str, 0, sizeof(str));
		}
		fclose(file);
	}
	return flag;
}

void error()
{
	printf("�� ����������� ����� ����� ������! ���������� ��� ���.\n\n");
}

void exit_menu()
{
	printf("����� ����������� ����� � ����, ������� 0: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && atoi(input) == 0)
	{
		system("cls");
		return;
	}
	else
	{
		printf("������������ ����! ���������� ��� ���.\n");
		exit_menu();
	}
}

// ����� ������� �����
void add_size()
{
	printf("������� ����� ������ � �������� �������� �����: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && atoi(input) > 0 && atoi(input) < 4)
	{
		pizza.size = atoi(input);
		if (pizza.size == SMALL) strcpy(pizza.sizename, sizename[0]);
		if (pizza.size == MIDDLE) strcpy(pizza.sizename, sizename[1]);
		if (pizza.size == BIG) strcpy(pizza.sizename, sizename[2]);
		printf("\n* �� ������� ����� ��� ����� �%d - %s *\n\n", pizza.size, pizza.sizename);
	}
	else
	{
		printf("�� ����������� ����� ����� ������. ���������� ��� ���!\n");
		add_size();
	}
}

// ���������� �����
void add_sauce()
{
	printf("������� ����� ������ � �������� ������ �����: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && atoi(input) > 0 && atoi(input) < 7)
	{
		pizza.base.sauce = atoi(input);
		for (int i = 1; i < 7; i++)
		{
			if (pizza.base.sauce == i) strcpy(pizza.base.saucename, sauce[i - 1]);
		}
		printf("\n* �� ������� �������� ���� ��� ����� - %s *\n\n", pizza.base.saucename);
	}
	else
	{
		printf("�� ����������� ����� ����� ������. ���������� ��� ���!\n");
		add_sauce();
	}
}

// ���������� ��������� ����
void add_cheese()
{
	printf("������� ����� ������ � �������� ����� ��� �����: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 5))
	{
		pizza.base.cheese = atoi(input);
		for (int i = 1; i < 5; i++)
		{
			if (pizza.base.cheese == i) strcpy(pizza.base.cheesename, cheese[i - 1]);
		}
		printf("\n* �� ������� �������� ��� ��� ����� - %s *\n\n", pizza.base.cheesename);
	}
	else
	{
		printf("�� ����������� ����� ����� ������. ���������� ��� ���!\n");
		add_cheese();
	}
}

// ����������� ������� �������
int check_fill(char* input)
{
	int ret = 0;
	if (pizza.size == SMALL)
	{
		if (strlen(input) < 4) ret = 1;
	}
	else if (pizza.size == MIDDLE)
	{
		if (strlen(input) < 6) ret = 1;
	}
	else if (pizza.size == BIG)
	{
		if (strlen(input) < 8) ret = 1;
	}
	return ret;
}

// ���������� ������� �������
void add_veg()
{
	printf("������� ������ ������� � �������� ������� �������� (��� �������): ");
	char input[MAX_NUMS_INPUT];
	fgets(input, MAX_NUMS_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	int flag = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		for (int j = i + 1; j < strlen(input); j++)
		{
			if ((input[i] - '0') == (input[j] - '0')) flag = 1;
		}
		if ((input[i] - '0') > 7) flag = 1;
	}
	if (security(input) == 0 && flag == 0 && check_fill(input) == 1)
	{
		// � ������� veg ������ +1 �� ����������� ������ �������
		for (int i = 0; i < strlen(input); i++)
		{
			pizza.fill.veg[(input[i] - '0') - 1] = 1;
		}
		printf("\n* �� �������� ������� ������� ��� ����� - ");
		for (int i = 0; i < strlen(input); i++)
		{
			if (pizza.size == SMALL) printf("%s, ", vegsmall[(input[i] - '0') - 1]);
			else if (pizza.size == MIDDLE) printf("%s, ", vegmid[(input[i] - '0') - 1]);
			else if (pizza.size == BIG) printf("%s, ", vegbig[(input[i] - '0') - 1]);
		}
		printf("*\n\n");
	}
	else
	{
		printf("�� ����������� ����� ������ �������. ���������� ��� ���!\n");
		memset(input, 0, sizeof(input));
		add_veg();
	}
}

// ���������� ������ �������
void add_meat()
{
	printf("������� ������ ������� � �������� ������ �������� (��� �������): ");
	char input[MAX_NUMS_INPUT];
	fgets(input, MAX_NUMS_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	int flag = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		for (int j = i + 1; j < strlen(input); j++)
		{
			if ((input[i] - '0') == (input[j] - '0')) flag = 1;
		}
		if ((input[i] - '0') > 7) flag = 1;
	}
	if (security(input) == 0 && flag == 0 && check_fill(input) == 1)
	{
		for (int i = 0; i < strlen(input); i++)
		{
			pizza.fill.meat[(input[i] - '0') - 1] = 1;
		}
		printf("\n* �� �������� ������ ������� ��� ����� - ");
		for (int i = 0; i < strlen(input); i++)
		{
			if (i + 1 == strlen(input))
			{
				printf("%s ", meat[(input[i] - '0') - 1]);
			}
			else printf("%s, ", meat[(input[i] - '0') - 1]);
		}
		printf("*\n\n");
	}
	else
	{
		printf("�� ����������� ����� ������ �������. ���������� ��� ���!\n");
		memset(input, 0, sizeof(input));
		add_meat();
	}
}

// ���������� ��������
void add_seas()
{
	printf("������� ����� ������ � �������� ��������� ��� �����: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && atoi(input) > 0 && atoi(input) < 4)
	{
		pizza.fill.seasonings = atoi(input);
		printf("\n* �� ������� �������� ��� ����� - %s *\n\n", seas[atoi(input) - 1]);
	}
	else
	{
		printf("�� ����������� ����� ����� ������. ���������� ��� ���!\n");
		add_seas();
	}
}

// �������� ����� �����
void create_new()
{
	if (pizza.size != 0)
	{
		printf("� ��� ��� ������� �����. ��� ����, ����� ������� �����, ���������� ������� ������.\n");
		printf("�� �������, ��� ������ ��������� ������� ������� �����?\n");
		printf("��� ������������� ������� 1, ��� �������� � ���� ������� 0: ");
		char input[MAX_DIGIT_INPUT];
		fgets(input, MAX_DIGIT_INPUT, stdin);
		fseek(stdin, 0, SEEK_END);
		if (security(input) == 0 && (atoi(input) == 1))
		{
			// ��������� ���������
			pizza.size = 0;
			memset(pizza.sizename, 0, sizeof(pizza.sizename));
			pizza.base.sauce = 0;
			memset(pizza.base.saucename, 0, sizeof(pizza.base.saucename));
			pizza.base.cheese = 0;
			memset(pizza.base.cheesename, 0, sizeof(pizza.base.cheesename));
			memset(pizza.fill.veg, 0, sizeof(pizza.fill.veg));
			memset(pizza.fill.meat, 0, sizeof(pizza.fill.meat));
			pizza.fill.seasonings = 0;
			system("cls");
			printf("���� ����� ������� �������!\n\n");
		}
		else if (security(input) == 0 && (atoi(input) == 0))
		{
			system("cls");
			return;
		}
		else
		{
			system("cls");
			printf("������������ ����! ���������� ��� ���.\n\n");
			create_new();
		}
	}
	printf("\"�������� ����� �����\"\n\n");
	printf("��� ������ �� ������ ������� ������ �������� �����:\n");
	for (int i = 0; i < 3; i++) printf("%d. %s (25 ��.) - %d ���.\n", i + 1, sizename[i], costs.sizecost[i]);
	add_size();

	printf("�����, �������� �������� ���� ��� �����:\n");
	for (int i = 0; i < 6; i++) printf("%d. %s - %d ���.\n", i + 1, sauce[i], costs.saucecost[i]);
	add_sauce();

	printf("�����, �������� �������� ��� ��� �����:\n");
	for (int i = 0; i < 4; i++) printf("%d. %s - %d ���.\n", i + 1, cheese[i], costs.cheesecost[i]);
	add_cheese();

	printf("������ ���������� ������� ������� ��� �����.\n");
	printf("�������� ������� ������� ��� �����:\n");
	if (pizza.size == SMALL)
	{
		for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, vegsmall[i], costs.vegcost[i]);
	}
	else if (pizza.size == MIDDLE)
	{
		for (int i = 0; i < 5; i++) printf("%d. %s - %d ���.\n", i + 1, vegmid[i], costs.vegcost[i]);
	}
	else if (pizza.size == BIG)
	{
		for (int i = 0; i < 7; i++) printf("%d. %s - %d ���.\n", i + 1, vegbig[i], costs.vegcost[i]);
	}
	add_veg();

	printf("�������� ������ ������� ��� �����:\n");
	if (pizza.size == SMALL)
	{
		for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
	}
	else if (pizza.size == MIDDLE)
	{
		for (int i = 0; i < 5; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
	}
	else if (pizza.size == BIG)
	{
		for (int i = 0; i < 7; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
	}
	add_meat();

	printf("�������� �������� ��� �����:\n");
	for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, seas[i], costs.seascost[i]);
	add_seas();
	
	printf("���� ����� ������� �������!\n\n");
	exit_menu();
}

// ����� ����� �� �����
void print_pizza()
{
	printf("������� �����:\n\n");
	printf("1. ����� ��� �����: %d) %s - %d ���.\n", pizza.size, pizza.sizename, costs.sizecost[pizza.size - 1]);
	printf("2. ����: %d) %s - %d ���.\n", pizza.base.sauce, pizza.base.saucename, costs.saucecost[pizza.base.sauce - 1]);
	printf("3. ���: %d) %s - %d ���.\n", pizza.base.cheese, pizza.base.cheesename, costs.cheesecost[pizza.base.cheese - 1]);
	printf("4. ������� �������: ");
	for (int i = 0; i < VEG_MAX_SIZE; i++)
	{
		if (pizza.fill.veg[i] != 0)
		{
			if (pizza.size == SMALL) printf("%d) %s - %d ���. ", i + 1, vegsmall[i], costs.vegcost[i]);
			else if (pizza.size == MIDDLE) printf("%d) %s - %d ���. ", i + 1, vegmid[i], costs.vegcost[i]);
			else if (pizza.size == BIG) printf("%d) %s - %d ���. ", i + 1, vegbig[i], costs.vegcost[i]);
		}
	}
	printf("\n5. ������ �������: ");
	for (int i = 0; i < MEAT_MAX_SIZE; i++)
	{
		if (pizza.fill.meat[i] != 0)
		{
			printf("%d) %s - %d ���. ", i + 1, meat[i], costs.meatcost[i]);
		}
	}
	printf("\n6. �������� ��� �����: ");
	printf("%d) %s - %d ���.\n\n", pizza.fill.seasonings, seas[pizza.fill.seasonings - 1], costs.seascost[pizza.fill.seasonings - 1]);
}

// ������� ��������� �����
void cost_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("�� ��� �� ��������� �����!\n\n");
		return;
	}
	printf("\"������� ��������� �����\"\n\n");
	print_pizza();
	int sum_pizza = 0, sum_veg = 0, sum_meat = 0;
	sum_pizza = costs.sizecost[pizza.size - 1] + costs.saucecost[pizza.base.sauce - 1] + costs.cheesecost[pizza.base.cheese - 1];
	for (int i = 0; i < VEG_MAX_SIZE; i++) if (pizza.fill.veg[i] != 0) sum_veg += costs.vegcost[i];
	for (int i = 0; i < MEAT_MAX_SIZE; i++) if (pizza.fill.meat[i] != 0) sum_meat += costs.meatcost[i];
	sum_pizza += sum_veg;
	sum_pizza += sum_meat;
	sum_pizza += costs.seascost[pizza.fill.seasonings - 1];
	printf("�������� ��������� ����� - %d ���.\n\n", sum_pizza);
	exit_menu();
}

// ���������� ����� � ����
void save_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("�� ��� �� ��������� �����!\n\n");
		return;
	}
	printf("\"���������� ����� � ����\"\n\n");
	print_pizza();
	
	printf("������� ��� �����, � ������� �� ������ ��������� ������� �����: ");
	char str[64];
	fgets(str, sizeof(str), stdin);
	str[strcspn(str, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("\n�� �������, ��� ������ ��������� ��������� ����� � ���� '%s'?\n", str);
	printf("���������� ���������� ������ ����� ���� �������!\n");
	printf("��� ������������� ������� 1, ��� �������� � ���� ������� 0: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) == 1))
	{
		FILE* file = fopen(str, "w");
		fprintf(file, "%d\n%s\n", pizza.size, pizza.sizename);
		fprintf(file, "%d\n%s\n", pizza.base.sauce, pizza.base.saucename);
		fprintf(file, "%d\n%s\n", pizza.base.cheese, pizza.base.cheesename);
		for (int i = 0; i < VEG_MAX_SIZE; i++)
		{
			if (pizza.fill.veg[i] != 0) fprintf(file, "%d", i + 1);
		}
		fprintf(file, "\n");
		for (int i = 0; i < MEAT_MAX_SIZE; i++)
		{
			if (pizza.fill.meat[i] != 0) fprintf(file, "%d", i + 1);
		}
		fprintf(file, "\n");
		fprintf(file, "%d\n", pizza.fill.seasonings);
		fclose(file);
		system("cls");
		printf("���� ����� ������� ��������� � ���� '%s'!\n\n", str);
	}
	else if (security(input) == 0 && (atoi(input) == 0))
	{
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("������������ ����! ���������� ��� ���.\n\n");
		save_pizza();
	}
}

// �������� ������� ����� �� �����
void open_pizza()
{
	printf("\"�������� ����� �� �����\"\n\n");
	printf("������� ��� �����, �� �������� �� ������ ��������� ������� �����: ");
	char input[64];
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	if (security_file(input) == 0)
	{
		system("cls");
		printf("������ � ����� '%s' ����������� / ���� �� ������. ���������� ��� ���!\n\n", input);
		open_pizza();
	}
	else
	{
		FILE* file = fopen(input, "r");
		char str[32];
		for (int i = 1; i < 10; i++)
		{
			fgets(str, sizeof(str), file);
			str[strcspn(str, "\n")] = 0;
			if (i == 1) pizza.size = atoi(str);
			else if (i == 2)
			{
				for (int j = 0; j < strlen(str); j++) pizza.sizename[j] = str[j];
			}
			else if (i == 3) pizza.base.sauce = atoi(str);
			else if (i == 4)
			{
				for (int j = 0; j < strlen(str); j++) pizza.base.saucename[j] = str[j];
			}
			else if (i == 5) pizza.base.cheese = atoi(str);
			else if (i == 6)
			{
				for (int j = 0; j < strlen(str); j++) pizza.base.cheesename[j] = str[j];
			}
			else if (i == 7)
			{
				for (int j = 0; j < strlen(str); j++) pizza.fill.veg[(str[j] - '0') - 1] = 1;
			}
			else if (i == 8)
			{
				for (int j = 0; j < strlen(str); j++) pizza.fill.meat[(str[j] - '0') - 1] = 1;
			}
			else if (i == 9) pizza.fill.seasonings = atoi(str);
			memset(str, 0, sizeof(str));
		}
		fclose(file);
	}
	system("cls");
	printf("����� �� ����� '%s' ������� �������!\n\n", input);
}

// �������� ��������� �����
void delete_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("�� ��� �� ��������� �����!\n\n");
		return;
	}
	printf("\"�������� ������� �����\"\n\n");
	printf("�� �������, ��� ������ ��������� ������� ������� �����?\n");
	printf("��� ������������� ������� 1, ��� �������� � ���� ������� 0: ");
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && (atoi(input) == 1))
	{
		// ��������� ���������
		pizza.size = 0;
		memset(pizza.sizename, 0, sizeof(pizza.sizename));
		pizza.base.sauce = 0;
		memset(pizza.base.saucename, 0, sizeof(pizza.base.saucename));
		pizza.base.cheese = 0;
		memset(pizza.base.cheesename, 0, sizeof(pizza.base.cheesename));
		memset(pizza.fill.veg, 0, sizeof(pizza.fill.veg));
		memset(pizza.fill.meat, 0, sizeof(pizza.fill.meat));
		pizza.fill.seasonings = 0;
		system("cls");
		printf("���� ����� ������� �������!\n\n");
	}
	else if (security(input) == 0 && (atoi(input) == 0))
	{
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("������������ ����! ���������� ��� ���.\n\n");
		delete_pizza();
	}
}

// �������� � ��������� ������� �����
void change_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("�� ��� �� ��������� �����!\n\n");
		return;
	}
	printf("\"�������� � ��������� ������� �����\"\n\n");
	print_pizza();
	printf("������� ����� ���������� ��� �����, ������� �� ������ ��������\n");
	printf("(���� �� ������ ����� � ����, ������� 0): ");
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 7))
	{
		if (atoi(input) == 1)
		{
			pizza.size = 0;
			memset(pizza.sizename, 0, sizeof(pizza.sizename));
			printf("\n1. %s (25 ��.) - %d ���.\n", sizename[0], costs.sizecost[0]);
			printf("2. %s (30 ��.) - %d ���.\n", sizename[1], costs.sizecost[1]);
			printf("3. %s (35 ��.) - %d ���.\n", sizename[2], costs.sizecost[2]);
			add_size();
			system("cls");
			printf("�� ������� �������� ������ �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 2)
		{
			pizza.base.sauce = 0;
			memset(pizza.base.saucename, 0, sizeof(pizza.base.saucename));
			for (int i = 0; i < 6; i++) printf("%d. %s - %d ���.\n", i + 1, sauce[i], costs.saucecost[i]);
			add_sauce();
			system("cls");
			printf("�� ������� �������� ���� ��� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 3)
		{
			pizza.base.cheese = 0;
			memset(pizza.base.cheesename, 0, sizeof(pizza.base.cheesename));
			for (int i = 0; i < 4; i++) printf("%d. %s - %d ���.\n", i + 1, cheese[i], costs.cheesecost[i]);
			add_cheese();
			system("cls");
			printf("�� ������� �������� �������� ��� ��� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 4)
		{
			memset(pizza.fill.veg, 0, sizeof(pizza.fill.veg));
			if (pizza.size == 1)
			{
				for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, vegsmall[i], costs.vegcost[i]);
			}
			else if (pizza.size == 2)
			{
				for (int i = 0; i < 5; i++) printf("%d. %s - %d ���.\n", i + 1, vegmid[i], costs.vegcost[i]);
			}
			else if (pizza.size == 3)
			{
				for (int i = 0; i < 7; i++) printf("%d. %s - %d ���.\n", i + 1, vegbig[i], costs.vegcost[i]);
			}
			add_veg();
			system("cls");
			printf("�� ������� �������� ������� ������� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 5)
		{
			memset(pizza.fill.meat, 0, sizeof(pizza.fill.meat));
			if (pizza.size == 1)
			{
				for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
			}
			else if (pizza.size == 2)
			{
				for (int i = 0; i < 5; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
			}
			else if (pizza.size == 3)
			{
				for (int i = 0; i < 7; i++) printf("%d. %s - %d ���.\n", i + 1, meat[i], costs.meatcost[i]);
			}
			add_meat();
			system("cls");
			printf("�� ������� �������� ������ ������� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 6)
		{
			pizza.fill.seasonings = 0;
			for (int i = 0; i < 3; i++) printf("%d. %s - %d ���.\n", i + 1, seas[i], costs.seascost[i]);
			add_seas();
			system("cls");
			printf("�� ������� �������� �������� ��� �����!\n\n");
			change_pizza();
		}
	}
	else if (security(input) == 0 && atoi(input) == 0)
	{
		system("cls");
		return;
	}
	else
	{
		printf("�� ����������� ����� ����� ������. ���������� ��� ���!\n");
		add_cheese();
	}
}

// ���������� ��� ����������� �� �����
void cost_init()
{
	int number[6] = { 0, 0, 0, 0, 0, 0 };
	char onecost[32];
	char str[64];
	FILE* file = fopen("costs.txt", "r");
	for (int i = 1; i < 31; i++)
	{
		fgets(str, sizeof(str), file);
		int count = 0;
		for (int j = 4; j < strlen(str); j++)
		{
			if (str[j] == ' ') break;
			onecost[count] = str[j];
			count++;
		}
		onecost[count] = '\0';
		count = 0;
		if (i >= 1 && i <= 3)
		{
			costs.sizecost[number[0]] = atoi(onecost);
			number[0]++;
		}
		else if (i >= 4 && i <= 9)
		{
			costs.saucecost[number[1]] = atoi(onecost);
			number[1]++;
		}
		else if (i >= 10 && i <= 13)
		{
			costs.cheesecost[number[2]] = atoi(onecost);
			number[2]++;
		}
		else if (i >= 14 && i <= 20)
		{
			costs.vegcost[number[3]] = atoi(onecost);
			number[3]++;
		}
		else if (i >= 21 && i <= 27)
		{
			costs.meatcost[number[4]] = atoi(onecost);
			number[4]++;
		}
		else if (i >= 28 && i <= 30)
		{
			costs.seascost[number[5]] = atoi(onecost);
			number[5]++;
		}
		memset(onecost, 0, sizeof(onecost));
	}
	fclose(file);
}

int menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("\"������������ �����\"\n\n"
		"1. ������� ����� ����������� �����.\n"
		"2. ����������/�������� ������� �����.\n"
		"3. ���������� ���� �����.\n"
		"4. ��������� ��������� ����� � ����.\n"
		"5. ������� ������� ����� �� �����.\n"
		"6. ������� ��������� �����.\n"
		"0. ����� �� ���������.\n"
		"\n�������� ����� ������ ������ ���������: ");

	int value = -1;
	char input[MAX_DIGIT_INPUT];
	fgets(input, MAX_DIGIT_INPUT, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && (atoi(input) < 7))
	{
		value = atoi(input);
		return value;
	}
	else return -1;
}

int main()
{
	cost_init();

	int n;
	n = menu();
	while (1)
	{
		switch (n)
		{
		case 1:
			system("cls");
			create_new();
			break;
		case 2:
			system("cls");
			change_pizza();
			break;
		case 3:
			system("cls");
			cost_pizza();
			break;
		case 4:
			system("cls");
			save_pizza();
			break;
		case 5:
			system("cls");
			open_pizza();
			break;
		case 6:
			system("cls");
			delete_pizza();
			break;
		case 0:
			system("cls");
			printf("�� ����� �� ���������.\n");
			return 0;
		default:
			system("cls");
			error();
			break;
		}
		n = menu();
	}
}