// Made by Y. Sendov. March 2022

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

union condition
{
	int SMALL;
	int MIDDLE;
	int BIG;
};

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
	char saucename[32];
	int cheese;
	char cheesename[32];
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
	char sizename[32];
	struct new_base base;
	struct new_fill fill;
	union condition info;
} pizza;

int security(char input[3])
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
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 3))
				{
					flag = 0;
				}
			}
			else if (i == 2)
			{
				if (strlen(str) > 9 || (strcmp(str, sizename[0]) != 0 && strcmp(str, sizename[1]) != 0 && strcmp(str, sizename[2]) != 0))
				{
					flag = 0;
				}
			}
			else if (i == 3)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 6))
				{
					flag = 0;
				}
			}
			else if (i == 4)
			{
				if (strlen(str) > 9 || (strcmp(str, sauce[0]) != 0 && strcmp(str, sauce[1]) != 0 && strcmp(str, sauce[2]) != 0 && strcmp(str, sauce[3]) != 0 && strcmp(str, sauce[4]) != 0 && strcmp(str, sauce[5]) != 0))
				{
					flag = 0;
				}
			}
			else if (i == 5)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 4)) 
				{
					flag = 0;
				}
			}
			else if (i == 6)
			{
				if (strlen(str) > 9 || (strcmp(str, cheese[0]) != 0 && strcmp(str, cheese[1]) != 0 && strcmp(str, cheese[2]) != 0 && strcmp(str, cheese[3]) != 0))
				{
					flag = 0;
				}
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
					if (isdigit(str[j]) == 0 || (isdigit(str[j]) != 0 && (str[j] - '0') > 7))
					{
						flag = 0;
					}
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
					if (isdigit(str[j]) == 0 || (isdigit(str[j]) != 0 && (str[j] - '0') > 7))
					{
						flag = 0;
					}
				}
			}
			else if (i == 9)
			{
				if (strlen(str) > 1 || isdigit(str[0]) == 0 || (isdigit(str[0]) != 0 && atoi(str) > 3))
				{
					flag = 0;
				}
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
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);
	if (security(input) == 0 && atoi(input) == 0)
	{
		system("cls");
		return;
	}
	else
	{
		printf("������������ ����! ���������� ��� ���. \n");
		exit_menu();
	}
}

// ����� ������� �����
void add_size()
{
	printf("������� ����� ������ � �������� �������� �����: ");

	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 4))
	{
		pizza.size = atoi(input);
		if (pizza.size == SMALL)
		{
			strcpy(pizza.sizename, sizename[0]);
			pizza.info.SMALL = 1;
		}
		if (pizza.size == MIDDLE)
		{
			strcpy(pizza.sizename, sizename[1]);
			pizza.info.MIDDLE = 2;
		}
		if (pizza.size == BIG)
		{
			strcpy(pizza.sizename, sizename[2]);
			pizza.info.BIG = 3;
		}
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
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 7))
	{
		pizza.base.sauce = atoi(input);
		if (pizza.base.sauce == 1) strcpy(pizza.base.saucename, sauce[0]);
		if (pizza.base.sauce == 2) strcpy(pizza.base.saucename, sauce[1]);
		if (pizza.base.sauce == 3) strcpy(pizza.base.saucename, sauce[2]);
		if (pizza.base.sauce == 4) strcpy(pizza.base.saucename, sauce[3]);
		if (pizza.base.sauce == 5) strcpy(pizza.base.saucename, sauce[4]);
		if (pizza.base.sauce == 6) strcpy(pizza.base.saucename, sauce[5]);
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
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 5))
	{
		pizza.base.cheese = atoi(input);
		if (pizza.base.cheese == 1) strcpy(pizza.base.cheesename, cheese[0]);
		if (pizza.base.cheese == 2) strcpy(pizza.base.cheesename, cheese[1]);
		if (pizza.base.cheese == 3) strcpy(pizza.base.cheesename, cheese[2]);
		if (pizza.base.cheese == 4) strcpy(pizza.base.cheesename, cheese[3]);
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
	if (pizza.info.SMALL == 1)
	{
		if (strlen(input) < 4) ret = 1;
	}
	else if (pizza.info.MIDDLE == 2)
	{
		if (strlen(input) < 6) ret = 1;
	}
	else if (pizza.info.BIG == 3)
	{
		if (strlen(input) < 8) ret = 1;
	}
	return ret;
}

// ���������� ������� �������
void add_veg()
{
	printf("������� ������ ������� � �������� ������� �������� (��� �������): ");
	char input[9];
	fgets(input, 9, stdin);
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
			if (pizza.info.SMALL == 1) printf("%s, ", vegsmall[(input[i] - '0') - 1]);
			else if (pizza.info.MIDDLE == 2) printf("%s, ", vegmid[(input[i] - '0') - 1]);
			else if (pizza.info.BIG == 3) printf("%s, ", vegbig[(input[i] - '0') - 1]);
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
	char input[9];
	fgets(input, 9, stdin);
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
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 4))
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

		char input[3];
		fgets(input, 3, stdin);
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
	printf("%d. %s (25 ��.) - %d ���.\n", SMALL, sizename[0], costs.sizecost[0]);
	printf("%d. %s (30 ��.) - %d ���.\n", MIDDLE, sizename[1], costs.sizecost[1]);
	printf("%d. %s (35 ��.) - %d ���.\n", BIG, sizename[2], costs.sizecost[2]);

	add_size();

	printf("�����, �������� �������� ���� ��� �����:\n");
	printf("1. %s - %d ���.\n", sauce[0], costs.saucecost[0]);
	printf("2. %s - %d ���.\n", sauce[1], costs.saucecost[1]);
	printf("3. %s - %d ���.\n", sauce[2], costs.saucecost[2]);
	printf("4. %s - %d ���.\n", sauce[3], costs.saucecost[3]);
	printf("5. %s - %d ���.\n", sauce[4], costs.saucecost[4]);
	printf("6. %s - %d ���.\n", sauce[5], costs.saucecost[5]);

	add_sauce();

	printf("�����, �������� �������� ��� ��� �����:\n");
	printf("1. %s - %d ���.\n", cheese[0], costs.cheesecost[0]);
	printf("2. %s - %d ���.\n", cheese[1], costs.cheesecost[1]);
	printf("3. %s - %d ���.\n", cheese[2], costs.cheesecost[2]);
	printf("4. %s - %d ���.\n", cheese[3], costs.cheesecost[3]);

	add_cheese();

	printf("������ ���������� ������� ������� ��� �����.\n");
	printf("�������� ������� ������� ��� �����:\n");

	if (pizza.info.SMALL == 1)
	{
		printf("1. %s - %d ���.\n", vegsmall[0], costs.vegcost[0]);
		printf("2. %s - %d ���.\n", vegsmall[1], costs.vegcost[1]);
		printf("3. %s - %d ���.\n", vegsmall[2], costs.vegcost[2]);
	}
	else if (pizza.info.MIDDLE == 2)
	{
		printf("1. %s - %d ���.\n", vegmid[0], costs.vegcost[0]);
		printf("2. %s - %d ���.\n", vegmid[1], costs.vegcost[1]);
		printf("3. %s - %d ���.\n", vegmid[2], costs.vegcost[2]);
		printf("4. %s - %d ���.\n", vegmid[3], costs.vegcost[3]);
		printf("5. %s - %d ���.\n", vegmid[4], costs.vegcost[4]);
	}
	else if (pizza.info.BIG == 3)
	{
		printf("1. %s - %d ���.\n", vegbig[0], costs.vegcost[0]);
		printf("2. %s - %d ���.\n", vegbig[1], costs.vegcost[1]);
		printf("3. %s - %d ���.\n", vegbig[2], costs.vegcost[2]);
		printf("4. %s - %d ���.\n", vegbig[3], costs.vegcost[3]);
		printf("5. %s - %d ���.\n", vegbig[4], costs.vegcost[4]);
		printf("6. %s - %d ���.\n", vegbig[5], costs.vegcost[5]);
		printf("7. %s - %d ���.\n", vegbig[6], costs.vegcost[6]);
	}

	add_veg();

	printf("�������� ������ ������� ��� �����:\n");

	if (pizza.info.SMALL == 1)
	{
		printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
	}
	else if (pizza.info.MIDDLE == 2)
	{
		printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
		printf("4. %s - %d ���.\n", meat[3], costs.meatcost[3]);
		printf("5. %s - %d ���.\n", meat[4], costs.meatcost[4]);
	}
	else if (pizza.info.BIG == 3)
	{
		printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
		printf("4. %s - %d ���.\n", meat[3], costs.meatcost[3]);
		printf("5. %s - %d ���.\n", meat[4], costs.meatcost[4]);
		printf("6. %s - %d ���.\n", meat[5], costs.meatcost[5]);
		printf("7. %s - %d ���.\n", meat[6], costs.meatcost[6]);
	}

	add_meat();

	printf("�������� �������� ��� �����:\n");
	printf("1. %s - %d ���.\n", seas[0], costs.seascost[0]);
	printf("2. %s - %d ���.\n", seas[1], costs.seascost[1]);
	printf("3. %s - %d ���.\n", seas[2], costs.seascost[2]);

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
			if (pizza.info.SMALL == 1) printf("%d) %s - %d ���. ", i + 1, vegsmall[i], costs.vegcost[i]);
			else if (pizza.info.MIDDLE == 2) printf("%d) %s - %d ���. ", i + 1, vegmid[i], costs.vegcost[i]);
			else if (pizza.info.BIG == 3) printf("%d) %s - %d ���. ", i + 1, vegbig[i], costs.vegcost[i]);
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
	char input[3];
	fgets(input, 3, stdin);
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
			if (i == 1)
			{
				pizza.size = atoi(str);
				if (atoi(str) == 1) pizza.info.SMALL = atoi(str);
				else if (atoi(str) == 2) pizza.info.MIDDLE = atoi(str);
				else if (atoi(str) == 3) pizza.info.BIG = atoi(str);
			}
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
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) == 1))
	{
		// ��������� ���������
		pizza.size = 0;
		pizza.info.SMALL = 0;
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
			pizza.info.SMALL = 0;
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
			printf("1. %s - %d ���.\n", sauce[0], costs.saucecost[0]);
			printf("2. %s - %d ���.\n", sauce[1], costs.saucecost[1]);
			printf("3. %s - %d ���.\n", sauce[2], costs.saucecost[2]);
			printf("4. %s - %d ���.\n", sauce[3], costs.saucecost[3]);
			printf("5. %s - %d ���.\n", sauce[4], costs.saucecost[4]);
			printf("6. %s - %d ���.\n", sauce[5], costs.saucecost[5]);
			add_sauce();
			system("cls");
			printf("�� ������� �������� ���� ��� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 3)
		{
			pizza.base.cheese = 0;
			memset(pizza.base.cheesename, 0, sizeof(pizza.base.cheesename));
			printf("1. %s - %d ���.\n", cheese[0], costs.cheesecost[0]);
			printf("2. %s - %d ���.\n", cheese[1], costs.cheesecost[1]);
			printf("3. %s - %d ���.\n", cheese[2], costs.cheesecost[2]);
			printf("4. %s - %d ���.\n", cheese[3], costs.cheesecost[3]);
			add_cheese();
			system("cls");
			printf("�� ������� �������� �������� ��� ��� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 4)
		{
			memset(pizza.fill.veg, 0, sizeof(pizza.fill.veg));
			if (pizza.info.SMALL == 1)
			{
				printf("1. %s - %d ���.\n", vegsmall[0], costs.vegcost[0]);
				printf("2. %s - %d ���.\n", vegsmall[1], costs.vegcost[1]);
				printf("3. %s - %d ���.\n", vegsmall[2], costs.vegcost[2]);
			}
			else if (pizza.info.MIDDLE == 2)
			{
				printf("1. %s - %d ���.\n", vegmid[0], costs.vegcost[0]);
				printf("2. %s - %d ���.\n", vegmid[1], costs.vegcost[1]);
				printf("3. %s - %d ���.\n", vegmid[2], costs.vegcost[2]);
				printf("4. %s - %d ���.\n", vegmid[3], costs.vegcost[3]);
				printf("5. %s - %d ���.\n", vegmid[4], costs.vegcost[4]);
			}
			else if (pizza.info.BIG == 3)
			{
				printf("1. %s - %d ���.\n", vegbig[0], costs.vegcost[0]);
				printf("2. %s - %d ���.\n", vegbig[1], costs.vegcost[1]);
				printf("3. %s - %d ���.\n", vegbig[2], costs.vegcost[2]);
				printf("4. %s - %d ���.\n", vegbig[3], costs.vegcost[3]);
				printf("5. %s - %d ���.\n", vegbig[4], costs.vegcost[4]);
				printf("6. %s - %d ���.\n", vegbig[5], costs.vegcost[5]);
				printf("7. %s - %d ���.\n", vegbig[6], costs.vegcost[6]);
			}
			add_veg();
			system("cls");
			printf("�� ������� �������� ������� ������� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 5)
		{
			memset(pizza.fill.meat, 0, sizeof(pizza.fill.meat));
			if (pizza.info.SMALL == 1)
			{
				printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
			}
			else if (pizza.info.MIDDLE == 2)
			{
				printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
				printf("4. %s - %d ���.\n", meat[3], costs.meatcost[3]);
				printf("5. %s - %d ���.\n", meat[4], costs.meatcost[4]);
			}
			else if (pizza.info.BIG == 3)
			{
				printf("1. %s - %d ���.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d ���.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d ���.\n", meat[2], costs.meatcost[2]);
				printf("4. %s - %d ���.\n", meat[3], costs.meatcost[3]);
				printf("5. %s - %d ���.\n", meat[4], costs.meatcost[4]);
				printf("6. %s - %d ���.\n", meat[5], costs.meatcost[5]);
				printf("7. %s - %d ���.\n", meat[6], costs.meatcost[6]);
			}
			add_meat();
			system("cls");
			printf("�� ������� �������� ������ ������� �����!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 6)
		{
			pizza.fill.seasonings = 0;
			printf("1. %s - %d ���.\n", seas[0], costs.seascost[0]);
			printf("2. %s - %d ���.\n", seas[1], costs.seascost[1]);
			printf("3. %s - %d ���.\n", seas[2], costs.seascost[2]);
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
	printf("\"������������ �����\"\n\n");
	printf("1. ������� ����� ����������� �����.\n");
	printf("2. ����������/�������� ������� �����.\n");
	printf("3. ���������� ���� �����.\n");
	printf("4. ��������� ��������� ����� � ����.\n");
	printf("5. ������� ������� ����� �� �����.\n");
	printf("6. ������� ��������� �����.\n");
	printf("0. ����� �� ���������.\n");
	printf("\n�������� ����� ������ ������ ���������: ");

	int value = -1;
	char input[3];
	fgets(input, 3, stdin);
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