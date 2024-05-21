#include <iostream>
const char STAGE_DATA[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";


const int STAGE_WIDTH{ 9 };
const int STAGE_HEIGHT{ 5 };


enum Object
{
    OBJ_SPACE,
    OBJ_WALL,
    OBJ_GOAL,
    OBJ_BLOCK,
    OBJ_BLOCK_ON_GOAL,
    OBJ_PLAYER,
    OBJ_PLAYER_ON_GOAL,
    OBJ_NEWLINE,

    OBJ_MAX
};




void Initialize(Object* state, int w, int h, const char* stageData) //초기화
{
    for (int i = 0; i < w * h; i++)
    {
        if (stageData[i] == '#')
        {
            state[i] = OBJ_WALL;
        }
        else if (stageData[i] == ' ')
        {
            state[i] = OBJ_SPACE;
        }
        else if (stageData[i] == '.')
        {
            state[i] = OBJ_GOAL;
        }
        else if (stageData[i] == 'o')
        {
            state[i] = OBJ_BLOCK;
        }
        else if (stageData[i] == 'O')
        {
            state[i] = OBJ_BLOCK_ON_GOAL;
        }
        else if (stageData[i] == 'p')
        {
            state[i] = OBJ_PLAYER;
        }
        else if (stageData[i] == 'P')
        {
            state[i] = OBJ_PLAYER_ON_GOAL;
        }
        else
        {
            state[i] = OBJ_NEWLINE;
        }
    }

}
void Draw(const Object* state, int w, int h)//그리기
{
    const char object_Draw[]{ ' ' , '#' , '.' , 'o' , 'O' , 'p' , 'P' , '\n' };
    for (int i = 0; i < w * h; i++)
    {
        std::cout << object_Draw[(state[i])];
    }

}
void Update(Object* state, char input, int w, int h)
{
    int move_x{ 0 };
    int move_y{ 0 };
    if (input == 'a')
    {
        move_x = -1;
    }
    else if (input == 'd')
    {
        move_x = 1;
    }
    else if (input == 'w')
    {
        move_y = -1;
    }
    else if (input == 's')
    {
        move_y = 1;
    }
    int player_x{ 0 }, player_y{ 0 };
    for (int i = 0; i < w * h; i++)
    {
        if (state[i] == OBJ_PLAYER || state[i] == OBJ_PLAYER_ON_GOAL)
        {
            player_x = i % w;
            player_y = i / w;
            break;
        }
    }
    int player_p = player_x + player_y * w;

    int player_move_x = player_x + move_x;
    int player_move_y = player_y + move_y;
    int player_move_p = player_move_x + player_move_y * w;

    if (state[player_move_p] == OBJ_WALL)
    {
        return;
    }

    int block_x = player_move_x + move_x;
    int block_y = player_move_y + move_y;

    int block_move_p = block_x + block_y * w;
    if (state[player_move_p] == OBJ_BLOCK || state[player_move_p] == OBJ_BLOCK_ON_GOAL)
    {
        if (state[block_move_p] == OBJ_GOAL)
        {
            state[block_move_p] = OBJ_BLOCK_ON_GOAL;
            state[player_move_p] = (state[player_move_p] == OBJ_BLOCK) ? OBJ_SPACE : OBJ_GOAL;
        }
        else if (state[block_move_p] == OBJ_SPACE)
        {
            state[block_move_p] = OBJ_BLOCK;
            state[player_move_p] = (state[player_move_p] == OBJ_BLOCK) ? OBJ_SPACE : OBJ_GOAL;
        }
        else
        {
            return;
        }
    }

    if (state[player_move_p] == OBJ_GOAL)
    {

        state[player_move_p] = OBJ_PLAYER_ON_GOAL;
        state[player_p] = (state[player_p] == OBJ_PLAYER) ? OBJ_SPACE : OBJ_GOAL;
    }
    else if (state[player_move_p] == OBJ_SPACE)
    {
        state[player_move_p] = OBJ_PLAYER;
        state[player_p] = (state[player_p] == OBJ_PLAYER) ? OBJ_SPACE : OBJ_GOAL;
    }

}
bool IsClear(const Object* state, int w, int h)
{
    for (int i = 0; i < w * h; i++)
    {
        if (state[i] == OBJ_BLOCK)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Object* stage = new Object[STAGE_WIDTH * STAGE_HEIGHT];


    Initialize(stage, STAGE_WIDTH, STAGE_HEIGHT, STAGE_DATA);


    while (true)
    {
        Draw(stage, STAGE_WIDTH, STAGE_HEIGHT);


        if (IsClear(stage, STAGE_WIDTH, STAGE_HEIGHT))
        {
            std::cout << std::endl << "CLEAR!!!" << std::endl;
            break;
        }


        char input{ };
        std::cout << "W: up, A: left, S: down, D: rightr, input : ";
        std::cin >> input;


        Update(stage, input, STAGE_WIDTH, STAGE_HEIGHT);


    }
}