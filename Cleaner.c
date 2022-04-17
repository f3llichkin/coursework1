#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <wincrypt.h>
int DoD(long Size, char Directory[MAX_PATH])
{
    if (Size <= 0)
    {
        printf("Ошибка аргумента\n");
        system("pause");
        return 1;
    }
    if (Directory == NULL)
    {
        printf("Ошибка аргумента\n");
        system("pause");
        return 2;
    }
    int Er;
    FILE* File;
    char Ch;
    HCRYPTPROV hProv = 0;
    BYTE* pbBuffer;
    BYTE* Inverse;
    int i;
    long Prohod = 0;
    if (printf("Удалить выбранный файл? Y/N\n") < 0)
    {
        printf("Ошибка printf в DoD.\n");
        system("pause");
        return 3;
    }
    getchar();
    Er = scanf("%c", &Ch);
    while (Er != 1 || (Ch != 'Y' && Ch != 'N'))
    {
        getchar();
        if (printf("Введите корректный выбор Y/N:\n") < 0)
        {
            printf("Ошибка в printf в DoD\n");
            system("pause");
            return 4;
        }
        Er = scanf("%c", &Ch);
        if (Er != 1)
        {
            printf("Ошибка в scanf в DoD!\n");
            system("pause");
            return 5;
        }
    }
    switch (Ch)
    {
    case 'Y':
        pbBuffer = (BYTE*)malloc(Size * sizeof(BYTE));
        if (pbBuffer == NULL)
        {
            printf("Ошибка выделения динамической памяти в DoD\n");
            system("pause");
            return 6;
        }
        Inverse = (BYTE*)malloc(Size * sizeof(BYTE));
        if (Inverse == NULL)
        {
            printf("Ошибка выделения динамической памяти в DoD\n");
            system("pause");
            free(pbBuffer);
            return 7;
        }
        for (i = 0; i <= 2; i++)
        {
            if ((i == 0) || (i == 2))
            {
                Er = CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
                if ((Er == FALSE))
                {
                    printf("Ошибка в CryptAcquireContextA в DoD");
                    system("pause");
                    free(Inverse);
                    free(pbBuffer);
                    return 8;
                }
                Er = CryptGenRandom(hProv, Size, pbBuffer);
                if (Er == FALSE)
                {
                    printf("Ошибка CryptGenRandom в DoD.\n");
                    system("pause");
                    free(Inverse);
                    free(pbBuffer);
                    CryptReleaseContext(hProv, 0);
                    return 9;
                }
                Er = CryptReleaseContext(hProv, 0);
                if (Er == FALSE)
                {
                    printf("Ошибка CryptReleaseContext в DoD.\n");
                    system("pause");
                    free(Inverse);
                    free(pbBuffer);
                    return 10;
                }
            }
            File = fopen(Directory, "rb+");
            if (File == NULL)
            {
                printf("Ошибка fopen() в DoD\n");
                system("pause");
                free(Inverse);
                free(pbBuffer);
                return 11;
            }

            if (fseek(File, 0, SEEK_SET) == -1)
            {
                printf("Ошибка fseek в DoD\n");
                system("pause");
                free(Inverse);
                free(pbBuffer);
                return 12;
            }
            do
            {
                if (i == 0)
                {
                    Inverse[Prohod] = ~(BYTE)pbBuffer[Prohod];
                    if (fwrite((void*)&pbBuffer[Prohod], sizeof(BYTE), 1, File) != 1)

                    {
                        printf("Ошибка fwrite в функции DoD!\n");
                        system("pause");
                        free(Inverse);
                        free(pbBuffer);
                        return 13;
                    }

                }
                if (i == 1)
                {
                    if (fwrite((void*)&Inverse[Prohod], sizeof(BYTE), 1, File)!= 1)
                    {
                        printf("Ошибка fwrite функции DoD!\n");
                        system("pause");
                        free(Inverse);
                        free(pbBuffer);
                        return 14;
                    }
                }
                if (i == 2)
                {

                    if (fwrite((void*)&Inverse[Prohod], sizeof(BYTE), 1, File) != 1)
                    {
                        printf("Ощибка fwrite в функции DoD!\n");
                        system("pause");
                        free(Inverse);
                        free(pbBuffer);
                        return 15;
                    }
                }
                Prohod++;
            } while (Prohod < Size);
            Er = fclose(File);
            if (Er != 0)
            {
                printf("Ошибка закрытия файла в DoD!");
                system("pause");
                free(Inverse);
                free(pbBuffer);
                return 16;
            }
        }
        free(pbBuffer);
        free(Inverse);
        if (remove(Directory) != 0)
        {
            printf("Удаление файла в DoD завершено с ошибкой!\n");
            system("pause");
            return 17;
        }
        else
        {
            if (printf("Файл успешно удален!\n") < 0)
            {
                printf("Ошибка printf в DoD.\n");
                system("pause");
                return 18;
            }
        }
        break;
    case 'N':
        if (printf("Файл не был удалён!\n") < 0)
        {
            printf("Ошибка printf в DoD.\n");
            system("pause");
            return 19;
        }
        return 0;
    default:
        printf("Некорректная обработка выбора\n");
        system("pause");
        return 20;
    }
    return 0;
}
int UserAlgoritm(long Size, char Link[MAX_PATH]) {
    if (Size <= 0)
    {
        printf("Ошибка аргумента\n");
        system("pause");
        return 1;
    }
    if (Link == NULL)
    {
        printf("Ошибка аргумента\n");
        system("pause");
        return 2;
    }
    int Plug, * Array, CycleCount = 0, MaxCycles;
    FILE* File;
    char Choice;
    if (printf("Введите число циклов, пожалуйста\n") < 0) {
        printf("Ошибка в printf в UserAlgoritm\n");
        system("pause");
        return 3;
    }
    Plug = scanf("%d", &MaxCycles);
    if (Plug != 1) {
        printf("Ошибка scanf в UserAlgoritm\n");
        system("pause");
        return 4;
    }
    while (MaxCycles < 1) {
        if (printf("Введите корректное число циклов\n") < 0) {
            printf("Ошибка printf в UserAlgoritm\n");
            system("pause");
            return 5;
        }
        Plug = scanf("%d", &MaxCycles);
        if (Plug != 1) {
            printf("Ошибка scanf в UserAlgoritm\n");
            system("pause");
            return 6;
        }
    }
    Array = (int*)malloc(MaxCycles * sizeof(int));
    if (Array == NULL)
    {
        printf("Ошибка выделения динамической памяти в UserAlgoritm\n");
        system("pause");
        return 7;
    }
    while (CycleCount < MaxCycles) {
        if (printf("Введите значение байта в %d цикле\n", CycleCount + 1) < 0) {
            printf("Ошибка в printf в UserAlgoritm\n");
            system("pause");
            free(Array);
            return 8;
        }
        Plug = scanf("%x", &Array[CycleCount]);
        if (Plug != 1) {
            printf("Ошибка в scanf в UserAlgoritm\n");
            system("pause");
            free(Array);
            return 9;
        }
        while (Plug == 0 || Array[CycleCount] < 0) {
            if (printf("Введите корректный байт\n") < 0) {
                printf("Ошибка printf в UserAlgoritm\n");
                system("pause");
                free(Array);
                return 10;
            }
            Plug = scanf("%x", &Array[CycleCount]);
            if (Plug != 1) {
                printf("Ошибка в scanf в UserAlgoritm\n");
                system("pause");
                free(Array);
                return 11;
            }
        }
        CycleCount++;
    }
    if (printf("Вы желаете удалить выбранный файл? y/n\n") < 0) {
        printf("Ошибка printf в UserAlgoritm\n");
        system("pause");
        free(Array);
        return 12;
    }
    getchar();
    Plug = scanf("%c", &Choice);
    while (Plug != 1 || (Choice != 'y' && Choice != 'n')) {
        getchar();
        if (printf("Введите корректный выбор y/n:\n") < 0) {
            printf("Ошибка в printf в UserAlgoritm");
            system("pause");
            free(Array);
            return 13;
        }
        Plug = scanf("%c", &Choice);
        if (Plug != 1) {
            printf("Ошибка в scanf в UserAlgoritm");
            system("pause");
            free(Array);
            return 14;
        }
    }
    switch (Choice) {
    case 'y': printf("Вы решили удалить!\n");
        for (int i = 0; i < MaxCycles; i++) {
            File = fopen(Link, "rb+");
            if (File == NULL) {
                printf("Ошибка fopen() в UserAlgoritm\n");
                system("pause");
                free(Array);
                return 15;
            }
            long Tictac = 0;
            if (fseek(File, 0, SEEK_SET) == -1) {
                printf("Ошибка fseek в UserAlgoritm");
                system("pause");
                free(Array);
                return 16;
            }
            while (Tictac < Size) {
                if (fwrite((void*)&Array[i], sizeof(BYTE), 1, File) != 1) {
                    printf("Ошибка fwrite в UserAlgoritm");
                    system("pause");
                    free(Array);
                    return 17;
                }
                Tictac++;
            }
            Plug = fclose(File);
            if (Plug != 0) {
                printf("Ошибка закрытия файла в UserAlgoritm");
                system("pause");
                free(Array);
                return 18;
            }
        }
        if (remove(Link) != 0) {
                printf("Ошибка в remove в UserAlgoritm");
                system("pause");
                free(Array);
                return 19;
        }
        free(Array);
        break;
    case 'n':
        return 0;
    default:
        if (printf("Некорректная обработка выбора\n") < 0) {
            printf("Ошибка в printf в UserAlgoritm");
            system("pause");
            return 20;
        }
        return 21;
    }
    return 0;
}
int main()
{
    int Error = 0;
    if (setlocale(LC_ALL, "Rus") == NULL) {
        printf("Ошибка в setlocale()\n");
        system("pause");
        return 1;
    }
    char Link[MAX_PATH];
    long Size = 0;
    int c;
    if (printf("Введите ссылку на файл, пожалуйста!\n") < 0) {
        printf("Ошибка в printf в main.\n");
        system("pause");
        return 2;
    }
    if (scanf("%[^\n]s", Link) != 1) {
        printf("Ошибка в scanf()");
        system("pause");
        return 3;
    }
    FILE* File = fopen(Link, "r+");
    if (File == NULL) {
        printf("Ошибка в fopen()\n");
        system("pause");
        return 4;
    }
    if (fseek(File, 0, SEEK_END) == -1) {
        printf("Ошибка в fseek()");
        system("pause");
        fclose(File);
        return 5;
    }
    Size = ftell(File);
    if (Size == -1) {
        printf("Ошибка в ftell()\n");
        system("pause");
        fclose(File);
        return 6;
    }
    Error = fclose(File);
    if (Error != 0) {
        printf("Ошибка в fclose()\n");
        system("pause");
        return 7;
    }
    if (printf("Выберите один из перечисленных алгоритмов уничтожения информации:\n") < 0) {
        printf("Ошибка в printf()\n");
        system("pause");
        return 8;
    }
    if (printf("a.Пользовательский\nb.DoD\nВведите номер выбранного метода:\n") < 0) {
        printf("Ошибка в printf()\n");
        system("pause");
        return 9;
    }
    getchar();
    c = getchar();
    if (c == EOF) {
        printf("Ошибка в getchar()\n");
        system("pause");
        return 10;
    }
    switch (c) {
    case 'a': if (printf("Вы выбрали пользовательский алгоритм удаления информации\n") < 0)
    {
        printf("Ошибка в printf()\n");
        system("pause");
        return 11;
    }
            if (UserAlgoritm(Size, Link) != 0) {
                printf("Некорректное выполнение UserAlgoritm()");
                system("pause");
                return 12;
            }
            break;
    case 'b':
        if (DoD(Size, Link) != 0)
        {
            printf("Некорректное выполнение DoD");
            system("pause");
            return 13;
        }
        break;
    default:
        printf("Ошибка выбора сценария\n");
        system("pause");
        return 14;
    }
    return 0;
}
