#include <iostream>
#include <string>
#include <array>
#include <cmath>

#define L_CONTACT 6
#define R_CONTACT 2

void r_rotate(std::array<int,8>& wheel);
void l_rotate(std::array<int,8>& wheel);
void R_chain(std::array<std::array<int,8>,4>& wheel, int num, int cnt);
void L_chain(std::array<std::array<int,8>,4>& wheel, int num, int cnt);
int score(std::array<std::array<int,8>,4>& wheel);

int main()
{
    std::array<std::array<int,8>,4> wheel;
    int gear = 8;
    int rotate_num;

    for(int i=0;i<wheel.size();i++)
    {
        std::string str;
        std::getline(std::cin,str);

        for(int j=0;j<str.size();j++)
        {
            wheel[i][j] = str[j]-'0';
        }
    }
    
    std::cin >> rotate_num;
    
    for(int i=0;i<rotate_num;i++)
    {
        int num;
        int dir;

        std::cin >> num;
        std::cin >> dir;

        R_chain(wheel,num,dir);
        L_chain(wheel,num,dir);
        if(dir == 1)
            r_rotate(wheel[num-1]);
        else if(dir == -1)
            l_rotate(wheel[num-1]);
        else
            std::cout << "dir must be -1 or 1" << std::endl;
    }

    int res = score(wheel);
    std::cout << res << std::endl;

    return 0;
}


void r_rotate(std::array<int,8>& wheel)
{
    int temp;
    temp = wheel[7];

    for(int i=6;i>=0;i--)
    {
        wheel[i+1] = wheel[i];
    }
    wheel[0] = temp;

}
void l_rotate(std::array<int,8>& wheel)
{
    int temp;
    temp = wheel[0];

    for(int i=0;i<8;i++)
    {
        wheel[i] = wheel[i+1];
    }
    wheel[7] = temp;
}

void R_chain(std::array<std::array<int,8>,4>& wheel, int num, int dir)
{

    if(num == 4)
    {
        return;
    }
    else
    {
        if(wheel[num-1][R_CONTACT] != wheel[num][L_CONTACT])
        {
            R_chain(wheel,num+1,-dir);
            if(dir == 1)
                l_rotate(wheel[num]);
            else    
                r_rotate(wheel[num]);
        }
      
    }
    return;
}

void L_chain(std::array<std::array<int,8>,4>& wheel, int num, int dir)
{
    if(num == 1)
    {
        return;
    }
    else
    {
        if(wheel[num-1][L_CONTACT] != wheel[num-2][R_CONTACT])
        {
            L_chain(wheel,num-1,-dir);

            if(dir == 1)
                l_rotate(wheel[num-2]);
            else
                r_rotate(wheel[num-2]);

        }
      
    }
    return;
}

int score(std::array<std::array<int,8>,4>& wheel)
{
    int score = 0;
    for(int i=0;i<wheel.size();i++)
    {
        // std::cout << i <<": " << wheel[i][0] << std::endl;
        score += wheel[i][0] * (pow(2,i));
    }
    return score;  
}