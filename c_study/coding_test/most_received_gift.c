#include <stdio.h>
#include <string.h>

#define MAX_FRIENDS 50
#define MAX_NAME_LEN 11

int findFriendIndex(char friends[MAX_FRIENDS][MAX_NAME_LEN], int friendCount, char *name) {
    for (int i = 0; i < friendCount; i++) {
        if (strcmp(friends[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int solution(char friends[MAX_FRIENDS][MAX_NAME_LEN], int friendCount, char gifts[][2][MAX_NAME_LEN], int giftCount) {
    int given[MAX_FRIENDS] = {0};
    int received[MAX_FRIENDS] = {0};
    int netGiftIndex[MAX_FRIENDS] = {0};
    int result[MAX_FRIENDS] = {0};

    // 선물 주고 받은 기록을 계산
    for (int i = 0; i < giftCount; i++) {
        int giverIndex = findFriendIndex(friends, friendCount, gifts[i][0]);
        int receiverIndex = findFriendIndex(friends, friendCount, gifts[i][1]);

        given[giverIndex]++;
        received[receiverIndex]++;
    }

    // 선물 지수 계산
    for (int i = 0; i < friendCount; i++) {
        netGiftIndex[i] = given[i] - received[i];
    }

    // 다음 달 선물 받는 수 예측
    for (int i = 0; i < friendCount; i++) {
        for (int j = 0; j < friendCount; j++) {
            if (i != j) {
                int giverToReceiver = 0;
                int receiverToGiver = 0;

                // gifts 기록에서 두 사람 간의 선물 횟수 계산
                for (int k = 0; k < giftCount; k++) {
                    if (strcmp(gifts[k][0], friends[i]) == 0 && strcmp(gifts[k][1], friends[j]) == 0) {
                        giverToReceiver++;
                    }
                    if (strcmp(gifts[k][0], friends[j]) == 0 && strcmp(gifts[k][1], friends[i]) == 0) {
                        receiverToGiver++;
                    }
                }

                if (giverToReceiver > receiverToGiver) {
                    result[j]++;
                } else if (giverToReceiver < receiverToGiver) {
                    result[i]++;
                } else if (netGiftIndex[i] > netGiftIndex[j]) {
                    result[j]++;
                } else if (netGiftIndex[i] < netGiftIndex[j]) {
                    result[i]++;
                }
            }
        }
    }

    // 가장 많이 선물 받는 친구 찾기
    int maxGifts = 0;
    for (int i = 0; i < friendCount; i++) {
        if (result[i] > maxGifts) {
            maxGifts = result[i];
        }
    }

    return maxGifts;
}

int main() {
    char friends[MAX_FRIENDS][MAX_NAME_LEN] = {"muzi", "ryan", "frodo", "neo"};
    char gifts[8][2][MAX_NAME_LEN] = {
        {"muzi", "frodo"},
        {"muzi", "frodo"},
        {"ryan", "muzi"},
        {"ryan", "muzi"},
        {"ryan", "muzi"},
        {"frodo", "muzi"},
        {"frodo", "ryan"},
        {"neo", "muzi"}
    };
    
    int result = solution(friends, 4, gifts, 8);
    printf("가장 많은 선물을 받는 친구는 %d개의 선물을 받을 것입니다.\n", result);
    
    return 0;
}
