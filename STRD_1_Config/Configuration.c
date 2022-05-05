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

// Константные имена компонентов
char sizename[3][10] = {
	"Маленькая", "Средняя", "Большая"
};
char sauce[6][10] = {
	"Томатный", "Альфредо", "Сливочный", "Чесночный", "Сметанный", "Песто"
};
char cheese[4][10] = {
	"Моцарелла", "Чеддер", "Пармезан", "Сулугуни"
};
char meat[7][24] = {
	"Ветчина", "Куриные кусочки", "Митболы", "Пикантная пепперони", "Цыплёнок", "Бекон", "Салями"
};
char seas[3][24] = {
	"Итальянские травы", "Кавказские травы", "Французские травы"
};

char vegbig[7][24] = {
	"Сладкий перец", "Красный лук", "Острый халапеньо", "Томаты", "Солёные огурчики", "Чеснок", "Шампиньоны"
};
char vegmid[5][24] = {
	"Баклажаны", "Маслины", "Ананасы", "Болгарский перец", "Кабачки"
};
char vegsmall[3][24] = {
	"Оливки", "Пряные корнишоны", "Свежая зелень"
};

// Структура для цен
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

// Структуры для пиццы
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
	// Проверка на существование файла
	if (file == NULL) flag = 0;
	else
	{
		// Проверка на содержание файла
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
	printf("Вы некорректно ввели номер режима! Попробуйте ещё раз.\n\n");
}

void exit_menu()
{
	printf("Чтобы подтвердить выход в меню, введите 0: ");
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
		printf("Некорректный ввод! Попробуйте ещё раз. \n");
		exit_menu();
	}
}

// Выбор размера пиццы
void add_size()
{
	printf("Введите номер пункта с желаемым размером пиццы: ");

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
		printf("\n* Вы выбрали тесто для пиццы №%d - %s *\n\n", pizza.size, pizza.sizename);
	}
	else
	{
		printf("Вы некорректно ввели номер пункта. Попробуйте ещё раз!\n");
		add_size();
	}
}

// Добавление соуса
void add_sauce()
{
	printf("Введите номер пункта с желаемым соусом пиццы: ");
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
		printf("\n* Вы выбрали основной соус для пиццы - %s *\n\n", pizza.base.saucename);
	}
	else
	{
		printf("Вы некорректно ввели номер пункта. Попробуйте ещё раз!\n");
		add_sauce();
	}
}

// Добавление основного сыра
void add_cheese()
{
	printf("Введите номер пункта с желаемым сыром для пиццы: ");
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
		printf("\n* Вы выбрали основной сыр для пиццы - %s *\n\n", pizza.base.cheesename);
	}
	else
	{
		printf("Вы некорректно ввели номер пункта. Попробуйте ещё раз!\n");
		add_cheese();
	}
}

// Вариативная овощная начинка
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

// Добавление овощной начинки
void add_veg()
{
	printf("Введите номера пунктов с желаемой овощной начинкой (без пробела): ");
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
		// В массиве veg делаем +1 по конкретному номеру начинки
		for (int i = 0; i < strlen(input); i++)
		{
			pizza.fill.veg[(input[i] - '0') - 1] = 1;
		}
		printf("\n* Вы добавили овощную начинку для пиццы - ");
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
		printf("Вы некорректно ввели номера пунктов. Попробуйте ещё раз!\n");
		memset(input, 0, sizeof(input));
		add_veg();
	}
}

// Добавление мясной начинки
void add_meat()
{
	printf("Введите номера пунктов с желаемой мясной начинкой (без пробела): ");
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
		printf("\n* Вы добавили мясную начинку для пиццы - ");
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
		printf("Вы некорректно ввели номера пунктов. Попробуйте ещё раз!\n");
		memset(input, 0, sizeof(input));
		add_meat();
	}
}

// Добавление приправы
void add_seas()
{
	printf("Введите номер пункта с желаемой приправой для пиццы: ");
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) > 0) && (atoi(input) < 4))
	{
		pizza.fill.seasonings = atoi(input);
		printf("\n* Вы выбрали приправу для пиццы - %s *\n\n", seas[atoi(input) - 1]);
	}
	else
	{
		printf("Вы некорректно ввели номер пункта. Попробуйте ещё раз!\n");
		add_seas();
	}
}

// Создание новой пиццы
void create_new()
{
	if (pizza.size != 0)
	{
		printf("У вас уже создана пицца. Для того, чтобы создать новую, необходимо удалить старую.\n");
		printf("Вы уверены, что хотите полностью удалить текущую пиццу?\n");
		printf("Для подтверждения введите 1, для возврата в меню введите 0: ");

		char input[3];
		fgets(input, 3, stdin);
		fseek(stdin, 0, SEEK_END);

		if (security(input) == 0 && (atoi(input) == 1))
		{
			// Обнуление структуры
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
			printf("Ваша пицца успешно удалена!\n\n");
		}
		else if (security(input) == 0 && (atoi(input) == 0))
		{
			system("cls");
			return;
		}
		else
		{
			system("cls");
			printf("Некорректный ввод! Попробуйте ещё раз.\n\n");
			create_new();
		}
	}

	printf("\"Создание новой пиццы\"\n\n");

	printf("Для начала вы должны выбрать размер желаемой пиццы:\n");
	printf("%d. %s (25 см.) - %d руб.\n", SMALL, sizename[0], costs.sizecost[0]);
	printf("%d. %s (30 см.) - %d руб.\n", MIDDLE, sizename[1], costs.sizecost[1]);
	printf("%d. %s (35 см.) - %d руб.\n", BIG, sizename[2], costs.sizecost[2]);

	add_size();

	printf("Далее, выберите основной соус для пиццы:\n");
	printf("1. %s - %d руб.\n", sauce[0], costs.saucecost[0]);
	printf("2. %s - %d руб.\n", sauce[1], costs.saucecost[1]);
	printf("3. %s - %d руб.\n", sauce[2], costs.saucecost[2]);
	printf("4. %s - %d руб.\n", sauce[3], costs.saucecost[3]);
	printf("5. %s - %d руб.\n", sauce[4], costs.saucecost[4]);
	printf("6. %s - %d руб.\n", sauce[5], costs.saucecost[5]);

	add_sauce();

	printf("Далее, выберите основной сыр для пиццы:\n");
	printf("1. %s - %d руб.\n", cheese[0], costs.cheesecost[0]);
	printf("2. %s - %d руб.\n", cheese[1], costs.cheesecost[1]);
	printf("3. %s - %d руб.\n", cheese[2], costs.cheesecost[2]);
	printf("4. %s - %d руб.\n", cheese[3], costs.cheesecost[3]);

	add_cheese();

	printf("Теперь необходимо выбрать начинку для пиццы.\n");
	printf("Выберите овощную начинку для пиццы:\n");

	if (pizza.info.SMALL == 1)
	{
		printf("1. %s - %d руб.\n", vegsmall[0], costs.vegcost[0]);
		printf("2. %s - %d руб.\n", vegsmall[1], costs.vegcost[1]);
		printf("3. %s - %d руб.\n", vegsmall[2], costs.vegcost[2]);
	}
	else if (pizza.info.MIDDLE == 2)
	{
		printf("1. %s - %d руб.\n", vegmid[0], costs.vegcost[0]);
		printf("2. %s - %d руб.\n", vegmid[1], costs.vegcost[1]);
		printf("3. %s - %d руб.\n", vegmid[2], costs.vegcost[2]);
		printf("4. %s - %d руб.\n", vegmid[3], costs.vegcost[3]);
		printf("5. %s - %d руб.\n", vegmid[4], costs.vegcost[4]);
	}
	else if (pizza.info.BIG == 3)
	{
		printf("1. %s - %d руб.\n", vegbig[0], costs.vegcost[0]);
		printf("2. %s - %d руб.\n", vegbig[1], costs.vegcost[1]);
		printf("3. %s - %d руб.\n", vegbig[2], costs.vegcost[2]);
		printf("4. %s - %d руб.\n", vegbig[3], costs.vegcost[3]);
		printf("5. %s - %d руб.\n", vegbig[4], costs.vegcost[4]);
		printf("6. %s - %d руб.\n", vegbig[5], costs.vegcost[5]);
		printf("7. %s - %d руб.\n", vegbig[6], costs.vegcost[6]);
	}

	add_veg();

	printf("Выберите мясную начинку для пиццы:\n");

	if (pizza.info.SMALL == 1)
	{
		printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
	}
	else if (pizza.info.MIDDLE == 2)
	{
		printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
		printf("4. %s - %d руб.\n", meat[3], costs.meatcost[3]);
		printf("5. %s - %d руб.\n", meat[4], costs.meatcost[4]);
	}
	else if (pizza.info.BIG == 3)
	{
		printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
		printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
		printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
		printf("4. %s - %d руб.\n", meat[3], costs.meatcost[3]);
		printf("5. %s - %d руб.\n", meat[4], costs.meatcost[4]);
		printf("6. %s - %d руб.\n", meat[5], costs.meatcost[5]);
		printf("7. %s - %d руб.\n", meat[6], costs.meatcost[6]);
	}

	add_meat();

	printf("Выберите приправу для пиццы:\n");
	printf("1. %s - %d руб.\n", seas[0], costs.seascost[0]);
	printf("2. %s - %d руб.\n", seas[1], costs.seascost[1]);
	printf("3. %s - %d руб.\n", seas[2], costs.seascost[2]);

	add_seas();
	
	printf("Ваша пицца успешно создана!\n\n");

	exit_menu();
}

// Вывод пиццы на экран
void print_pizza()
{
	printf("Текущая пицца:\n\n");
	printf("1. Тесто для пиццы: %d) %s - %d руб.\n", pizza.size, pizza.sizename, costs.sizecost[pizza.size - 1]);
	printf("2. Соус: %d) %s - %d руб.\n", pizza.base.sauce, pizza.base.saucename, costs.saucecost[pizza.base.sauce - 1]);
	printf("3. Сыр: %d) %s - %d руб.\n", pizza.base.cheese, pizza.base.cheesename, costs.cheesecost[pizza.base.cheese - 1]);
	printf("4. Овощная начинка: ");
	for (int i = 0; i < VEG_MAX_SIZE; i++)
	{
		if (pizza.fill.veg[i] != 0)
		{
			if (pizza.info.SMALL == 1) printf("%d) %s - %d руб. ", i + 1, vegsmall[i], costs.vegcost[i]);
			else if (pizza.info.MIDDLE == 2) printf("%d) %s - %d руб. ", i + 1, vegmid[i], costs.vegcost[i]);
			else if (pizza.info.BIG == 3) printf("%d) %s - %d руб. ", i + 1, vegbig[i], costs.vegcost[i]);
		}
	}
	printf("\n5. Мясная начинка: ");
	for (int i = 0; i < MEAT_MAX_SIZE; i++)
	{
		if (pizza.fill.meat[i] != 0)
		{
			printf("%d) %s - %d руб. ", i + 1, meat[i], costs.meatcost[i]);
		}
	}
	printf("\n6. Приправа для пиццы: ");
	printf("%d) %s - %d руб.\n\n", pizza.fill.seasonings, seas[pizza.fill.seasonings - 1], costs.seascost[pizza.fill.seasonings - 1]);
}

// Подсчёт стоимости пиццы
void cost_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("Вы ещё не создавали пиццу!\n\n");
		return;
	}

	printf("\"Подсчёт стоимости пиццы\"\n\n");
	
	print_pizza();

	int sum_pizza = 0, sum_veg = 0, sum_meat = 0;
	sum_pizza = costs.sizecost[pizza.size - 1] + costs.saucecost[pizza.base.sauce - 1] + costs.cheesecost[pizza.base.cheese - 1];
	for (int i = 0; i < VEG_MAX_SIZE; i++) if (pizza.fill.veg[i] != 0) sum_veg += costs.vegcost[i];
	for (int i = 0; i < MEAT_MAX_SIZE; i++) if (pizza.fill.meat[i] != 0) sum_meat += costs.meatcost[i];
	sum_pizza += sum_veg;
	sum_pizza += sum_meat;
	sum_pizza += costs.seascost[pizza.fill.seasonings - 1];

	printf("Итоговая стоимость пиццы - %d руб.\n\n", sum_pizza);

	exit_menu();
}

// Сохранение пиццы в файл
void save_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("Вы ещё не создавали пиццу!\n\n");
		return;
	}
	printf("\"Сохранение пиццы в файл\"\n\n");
	print_pizza();
	
	printf("Введите имя файла, в который вы хотите сохранить готовую пиццу: ");
	char str[64];
	fgets(str, sizeof(str), stdin);
	str[strcspn(str, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("\nВы уверены, что хотите сохранить созданную пиццу в файл '%s'?\n", str);
	printf("Предыдущие сохранённые данные могут быть удалены!\n");
	printf("Для подтверждения введите 1, для возврата в меню введите 0: ");
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
		printf("Ваша пицца успешно сохранена в файл '%s'!\n\n", str);
	}
	else if (security(input) == 0 && (atoi(input) == 0))
	{
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("Некорректный ввод! Попробуйте ещё раз.\n\n");
		save_pizza();
	}
}

// Открытие готовой пиццы из файла
void open_pizza()
{
	printf("\"Открытие пиццы из файла\"\n\n");

	printf("Введите имя файла, из которого вы хотите загрузить готовую пиццу: ");
	char input[64];
	fgets(input, sizeof(input), stdin);
	input[strcspn(input, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	if (security_file(input) == 0)
	{
		system("cls");
		printf("Данные в файле '%s' некорректны / Файл не найден. Попробуйте ещё раз!\n\n", input);
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
	printf("Пицца из файла '%s' успешно считана!\n\n", input);
}

// Удаление созданной пиццы
void delete_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("Вы ещё не создавали пиццу!\n\n");
		return;
	}

	printf("\"Удаление текущей пиццы\"\n\n");

	printf("Вы уверены, что хотите полностью удалить текущую пиццу?\n");
	printf("Для подтверждения введите 1, для возврата в меню введите 0: ");
	char input[3];
	fgets(input, 3, stdin);
	fseek(stdin, 0, SEEK_END);

	if (security(input) == 0 && (atoi(input) == 1))
	{
		// Обнуление структуры
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
		printf("Ваша пицца успешно удалена!\n\n");
	}
	else if (security(input) == 0 && (atoi(input) == 0))
	{
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("Некорректный ввод! Попробуйте ещё раз.\n\n");
		delete_pizza();
	}
}

// Просмотр и изменение готовой пиццы
void change_pizza()
{
	if (pizza.size == 0)
	{
		system("cls");
		printf("Вы ещё не создавали пиццу!\n\n");
		return;
	}

	printf("\"Просмотр и изменение текущей пиццы\"\n\n");
	print_pizza();
	printf("Введите номер компонента для пиццы, который вы хотите изменить\n");
	printf("(если вы хотите выйти в меню, введите 0): ");
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
			printf("\n1. %s (25 см.) - %d руб.\n", sizename[0], costs.sizecost[0]);
			printf("2. %s (30 см.) - %d руб.\n", sizename[1], costs.sizecost[1]);
			printf("3. %s (35 см.) - %d руб.\n", sizename[2], costs.sizecost[2]);
			add_size();
			system("cls");
			printf("Вы успешно изменили размер пиццы!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 2)
		{
			pizza.base.sauce = 0;
			memset(pizza.base.saucename, 0, sizeof(pizza.base.saucename));
			printf("1. %s - %d руб.\n", sauce[0], costs.saucecost[0]);
			printf("2. %s - %d руб.\n", sauce[1], costs.saucecost[1]);
			printf("3. %s - %d руб.\n", sauce[2], costs.saucecost[2]);
			printf("4. %s - %d руб.\n", sauce[3], costs.saucecost[3]);
			printf("5. %s - %d руб.\n", sauce[4], costs.saucecost[4]);
			printf("6. %s - %d руб.\n", sauce[5], costs.saucecost[5]);
			add_sauce();
			system("cls");
			printf("Вы успешно изменили соус для пиццы!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 3)
		{
			pizza.base.cheese = 0;
			memset(pizza.base.cheesename, 0, sizeof(pizza.base.cheesename));
			printf("1. %s - %d руб.\n", cheese[0], costs.cheesecost[0]);
			printf("2. %s - %d руб.\n", cheese[1], costs.cheesecost[1]);
			printf("3. %s - %d руб.\n", cheese[2], costs.cheesecost[2]);
			printf("4. %s - %d руб.\n", cheese[3], costs.cheesecost[3]);
			add_cheese();
			system("cls");
			printf("Вы успешно изменили основной сыр для пиццы!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 4)
		{
			memset(pizza.fill.veg, 0, sizeof(pizza.fill.veg));
			if (pizza.info.SMALL == 1)
			{
				printf("1. %s - %d руб.\n", vegsmall[0], costs.vegcost[0]);
				printf("2. %s - %d руб.\n", vegsmall[1], costs.vegcost[1]);
				printf("3. %s - %d руб.\n", vegsmall[2], costs.vegcost[2]);
			}
			else if (pizza.info.MIDDLE == 2)
			{
				printf("1. %s - %d руб.\n", vegmid[0], costs.vegcost[0]);
				printf("2. %s - %d руб.\n", vegmid[1], costs.vegcost[1]);
				printf("3. %s - %d руб.\n", vegmid[2], costs.vegcost[2]);
				printf("4. %s - %d руб.\n", vegmid[3], costs.vegcost[3]);
				printf("5. %s - %d руб.\n", vegmid[4], costs.vegcost[4]);
			}
			else if (pizza.info.BIG == 3)
			{
				printf("1. %s - %d руб.\n", vegbig[0], costs.vegcost[0]);
				printf("2. %s - %d руб.\n", vegbig[1], costs.vegcost[1]);
				printf("3. %s - %d руб.\n", vegbig[2], costs.vegcost[2]);
				printf("4. %s - %d руб.\n", vegbig[3], costs.vegcost[3]);
				printf("5. %s - %d руб.\n", vegbig[4], costs.vegcost[4]);
				printf("6. %s - %d руб.\n", vegbig[5], costs.vegcost[5]);
				printf("7. %s - %d руб.\n", vegbig[6], costs.vegcost[6]);
			}
			add_veg();
			system("cls");
			printf("Вы успешно изменили овощную начинку пиццы!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 5)
		{
			memset(pizza.fill.meat, 0, sizeof(pizza.fill.meat));
			if (pizza.info.SMALL == 1)
			{
				printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
			}
			else if (pizza.info.MIDDLE == 2)
			{
				printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
				printf("4. %s - %d руб.\n", meat[3], costs.meatcost[3]);
				printf("5. %s - %d руб.\n", meat[4], costs.meatcost[4]);
			}
			else if (pizza.info.BIG == 3)
			{
				printf("1. %s - %d руб.\n", meat[0], costs.meatcost[0]);
				printf("2. %s - %d руб.\n", meat[1], costs.meatcost[1]);
				printf("3. %s - %d руб.\n", meat[2], costs.meatcost[2]);
				printf("4. %s - %d руб.\n", meat[3], costs.meatcost[3]);
				printf("5. %s - %d руб.\n", meat[4], costs.meatcost[4]);
				printf("6. %s - %d руб.\n", meat[5], costs.meatcost[5]);
				printf("7. %s - %d руб.\n", meat[6], costs.meatcost[6]);
			}
			add_meat();
			system("cls");
			printf("Вы успешно изменили мясную начинку пиццы!\n\n");
			change_pizza();
		}
		else if (atoi(input) == 6)
		{
			pizza.fill.seasonings = 0;
			printf("1. %s - %d руб.\n", seas[0], costs.seascost[0]);
			printf("2. %s - %d руб.\n", seas[1], costs.seascost[1]);
			printf("3. %s - %d руб.\n", seas[2], costs.seascost[2]);
			add_seas();
			system("cls");
			printf("Вы успешно изменили приправу для пиццы!\n\n");
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
		printf("Вы некорректно ввели номер пункта. Попробуйте ещё раз!\n");
		add_cheese();
	}
}

// Считывание цен компонентов из файла
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
	printf("\"Конфигуратор пиццы\"\n\n");
	printf("1. Создать новую собственную пиццу.\n");
	printf("2. Посмотреть/изменить текущую пиццу.\n");
	printf("3. Рассчитать цену пиццы.\n");
	printf("4. Сохранить созданную пиццу в файл.\n");
	printf("5. Открыть готовую пиццу из файла.\n");
	printf("6. Удалить созданную пиццу.\n");
	printf("0. Выход из программы.\n");
	printf("\nВыберите номер режима работы программы: ");

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
			printf("Вы вышли из программы.\n");
			return 0;
		default:
			system("cls");
			error();
			break;
		}
		n = menu();
	}
}