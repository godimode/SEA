#define MAX_NAME_LEN (4+1)
#define MAX_USER 30001
#define MAX_GROUP 21
#define MAX_ACCOUNT 100001
#define MAX_HASH 1000001

struct Account {
    int userCur;
    int groupCur;
    int asset;
    int time;
    int isDel;
    int next;
    int prev;
    int state; // receive : 1, send : 0
}account[MAX_ACCOUNT];
int userNum, groupNum, ckck;
int userInfo[MAX_USER], groupInfo[MAX_GROUP];
int userIdx[MAX_HASH], groupIdx[MAX_HASH];
int priorityAccount[MAX_USER][MAX_GROUP];

int getHash(char name[]) {
    int h = 0;
    for (int i = 0; name[i]; i++) {
        h = (h << 5) + name[i] - 'a' + 1;
    }
    return h;
}

void init() {
    ckck++;
    for (int i = 1; i <= userNum; i++) {
        for (int j = 1; j <= groupNum; j++) {
            priorityAccount[i][j] = 0;
        }
    }
    for (int i = 1; i <= userNum; i++) {
        userIdx[userInfo[i]] = 0;
        userInfo[i] = 0;
    }
    for (int i = 1; i <= groupNum; i++) {
        groupIdx[groupInfo[i]] = 0;
        groupInfo[i] = 0;
    }
    userNum = groupNum = 0;
}
void add(int time, int userCur, int groupCur, int mNumber, int mAsset, int state) {

    account[mNumber].time = time;
    account[mNumber].asset = mAsset;
    account[mNumber].userCur = userCur;
    account[mNumber].groupCur = groupCur;
    account[mNumber].isDel = ckck;
    account[mNumber].prev = -1;
    account[mNumber].state = state;
    account[mNumber].next = priorityAccount[userCur][groupCur];
    if (priorityAccount[userCur][groupCur] != 0)
        account[priorityAccount[userCur][groupCur]].prev = mNumber;
    priorityAccount[userCur][groupCur] = mNumber;
}
void del(int mNumber) {
    int userCur = account[mNumber].userCur;
    int groupCur = account[mNumber].groupCur;
    if (account[mNumber].next == 0 && account[mNumber].prev == -1) {
        priorityAccount[userCur][groupCur] = 0;
    }
    else if (account[mNumber].next == 0) {
        account[account[mNumber].prev].next = 0;
    }
    else if (account[mNumber].prev == -1) {
        priorityAccount[userCur][groupCur] = account[mNumber].next;
        account[account[mNumber].next].prev = -1;
    }
    else {
        account[account[mNumber].prev].next = account[mNumber].next;
        account[account[mNumber].next].prev = account[mNumber].prev;
    }
}

void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset) {

    int nameHash = getHash(mName);
    int groupHash = getHash(mGroup);
    int userCur, groupCur;

    if (userIdx[nameHash] == 0) {
        userIdx[nameHash] = ++userNum;
        userInfo[userNum] = nameHash;
        userCur = userNum;
    }
    else
        userCur = userIdx[nameHash];

    if (groupIdx[groupHash] == 0) {
        groupIdx[groupHash] = ++groupNum;
        groupInfo[groupNum] = groupHash;
        groupCur = groupNum;
    }
    else
        groupCur = groupIdx[groupHash];

    add(mTime, userCur, groupCur, mNumber, mAsset, 0);
}

int closeAccount(int mTime, int mNumber) {
    del(mNumber);
    account[mNumber].isDel = 0;
    return account[mNumber].asset;
}

int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue) {

    if (account[mNumber].isDel != ckck || account[mReceiveNumber].isDel != ckck) return -1;
    if (account[mNumber].asset - mValue < 0) return -1;

    del(mNumber);
    add(mTime, account[mNumber].userCur, account[mNumber].groupCur, mNumber, account[mNumber].asset - mValue, 0);

    del(mReceiveNumber);
    add(mTime, account[mReceiveNumber].userCur, account[mReceiveNumber].groupCur, mReceiveNumber, account[mReceiveNumber].asset + mValue, 1);

    return account[mReceiveNumber].asset;
}

int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue) {

    int nameHash = getHash(mReceiveName);
    int userCur = userIdx[nameHash];
    int mReceiveNumber = 0;
    int maxTime = -1;
    int state = -1;

    for (int i = 1; i <= groupNum; i++) {
        int mAccount = priorityAccount[userCur][i];
        if (account[mAccount].isDel == ckck) {
            if(account[mAccount].time > maxTime) {
                mReceiveNumber = mAccount;
                maxTime = account[mAccount].time;
                state = account[mAccount].state;
            }
            else if (account[mAccount].time == maxTime && account[mAccount].state > state) {
                mReceiveNumber = mAccount;
                maxTime = account[mAccount].time;
                state = account[mAccount].state;
            }
        }
    }
    return sendByNumber(mTime, mNumber, mReceiveNumber, mValue);
}

void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue) {
    
    int groupHash = getHash(mGroup);
    int groupCur = groupIdx[groupHash];
    int mReceiveNumber;
    
    for (int i = 1; i <= userNum; i++) {
        int mAccount = priorityAccount[i][groupCur];
        if (mAccount) {
            account[mAccount].time = mTime;
            account[mAccount].asset += mValue;
            account[mAccount].state = 0;
        }
    }
}