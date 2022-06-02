// ConsoleStaples.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>
#include <string>
#include <map>

bool operator==( std::pair<char, char> & p1, char &p_1)
{
    return (p1.first == p_1);
}


struct stack
{
protected:
    std::set < std::pair<char, char> > open_close_staples[3] = { {'<','>'},{'{','}'}, {'(',')'} };

    char staple;
    stack* prev = 0;
    stack* head;

public:
   
    stack()
    {
        head = 0;
        prev = 0;
    }

    std::pair<char, char>& find(std::set < std::pair<char, char> >* s, char c)
    {
       std::pair<char, char>* p_res=nullptr;
       for (int i=0;i<3;i++)
           //]; p != open_close_staples[2];)
       {
           std::pair<char, char> p = open_close_staples[i].at();
           if (*p[0] == c) p_res = p;
       }
//       for (const auto p : open_close_staples) 
//           if (p.first == c) p_res = &p;

       return p_res;
    }
    bool is_open_staple(char c) //не получилось сделать static
    {
       
        return (open_close_staples.find(c) != open_close_staples.end());
    }
    bool is_close_staple(char c) 
    {
        return (open_close_staples.find(c) != open_close_staples.end());
    }
    static bool is_pair(char c, char c1)
    {
        return true;
    }
    void push_back(char t) 
    {
        stack* new_head = new stack();
        new_head->staple = t;
        new_head->prev = head;

        head = new_head;
    }

    char pop_back() 
    {
        if (head == 0) return -1;
        
        char res = head->staple;
        stack* del_head = head;
        head = head->prev;
        delete(del_head);
        return res;
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите выражение со скобками";
    stack S;

    std::string str;
    std::cin >> str;
    char c = str.c_str()[0];
    int len = strlen(str.c_str());
    int i = 0;
    do    {
            if (S.is_open_staple(c)) 
            S.push_back(c);
        else
            if (S.is_close_staple(c))
            {
                char c1 = S.pop_back();
                if (!S.is_pair(c, c1)) std::cout << "Ошибка!";
            }
            c = str.c_str()[i++];
            //c = str[i++];
    } while (i<len);

}

