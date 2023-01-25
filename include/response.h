#ifndef RESPONSE_H_
#define RESPONSE_H_
#include <stdbool.h>
#include "index.h"
typedef struct _resRD
{
    bool success;
    char message[100];
} ResRD;
typedef struct _findRoomResD
{
    RoomInfo Room[10];
    int roomSize;
} FindRoomResD;
typedef struct _updateRoomResD
{
    int playerSize; // number of players in room (2 -> 4)
    Player player[MAX_PLAYER];
} UpdateRoomResD;
typedef struct _chatResD
{
    char username[20];
    char message[100];
} ChatResD;
typedef struct _newGameResD
{
    bool isTurn;                      // true if first turn is your turn
    int playerSize;                   // playerSize = 2 -> 4
    Player player[MAX_PLAYER];        // player[0] is you
    Card cardInHand[CARD_VALUE_SIZE]; // 13 cards in hand
} NewGameResD;
typedef struct _playResD
{
    int playerTurn;                    // next turn (0 - 3)
    int playerSize;                    // number of players in room (2 -> 4)
    Player player[MAX_PLAYER];         // player[0] is you
    int cardInTableSize;               // number of card in table
    Card cardInTable[CARD_VALUE_SIZE]; // card in table
} PlayResD;

typedef enum _ResT
{
    FIND_ROOM_RES,   // find room response from server
    UPDATE_ROOM_RES, // update room properties from server
    NEW_GAME_RES,    // new game properties from server
    GAME_RES,        // update game properties from server
    CHAT_RES,        // update chat properties from server
    R_RES            // Response for request from client
} ResT;
typedef union _resD
{
    FindRoomResD findRoom;
    UpdateRoomResD updateRoom;
    NewGameResD newGame;
    PlayResD play;
    ChatResD chat;
    ResRD resR;
} ResD;

typedef struct _response
{
    ResT type;
    ResD data;
} Res;

Res createResponse(ResT type, ResD data)
{
    Res res;
    res.type = type;
    res.data = data;
    return res;
}
Res createFindRoomResponse(RoomInfo Room[10], int roomSize)
{
    FindRoomResD data;
    data.roomSize = roomSize;
    for (int i = 0; i < roomSize; i++)
    {
        data.Room[i] = Room[i];
    }
    return createResponse(FIND_ROOM_RES, (ResD)data);
}
Res createUpdateRoomResponse(int playerSize, Player player[MAX_PLAYER])
{
    UpdateRoomResD data;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    return createResponse(UPDATE_ROOM_RES, (ResD)data);
}
Res createNewGameResponse(bool isTurn, int playerSize, Player player[MAX_PLAYER], Card cardInHand[CARD_VALUE_SIZE])
{
    NewGameResD data;
    data.isTurn = isTurn;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    for (int i = 0; i < CARD_VALUE_SIZE; i++)
    {
        data.cardInHand[i] = cardInHand[i];
    }
    return createResponse(NEW_GAME_RES, (ResD)data);
}

Res createPlayResponse(int playerTurn, int playerSize, Player player[MAX_PLAYER], int cardInTableSize, Card cardInTable[CARD_VALUE_SIZE])
{
    PlayResD data;
    data.playerTurn = playerTurn;
    data.playerSize = playerSize;
    for (int i = 0; i < playerSize; i++)
    {
        data.player[i] = player[i];
    }
    data.cardInTableSize = cardInTableSize;
    for (int i = 0; i < cardInTableSize; i++)
    {
        data.cardInTable[i] = cardInTable[i];
    }
    return createResponse(GAME_RES, (ResD)data);
}

Res createChatResponse(char username[20], char message[100])
{
    ChatResD data;
    strcpy(data.username, username);
    strcpy(data.message, message);
    return createResponse(CHAT_RES, (ResD)data);
}

Res createRResponse(bool success, char message[100])
{
    ResRD data;
    data.success = success;
    strcpy(data.message, message);
    return createResponse(R_RES, (ResD)data);
}

#endif // RESPONSE_H_