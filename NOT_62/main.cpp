//
//  main.cpp
//  NOT_62
//
//  Created by Trinity on 16/3/2.
//  Copyright © 2016年 Trinity. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int dp[10][3];
void genDp(){
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for(int i = 1; i <= 6; i++) {
        dp[i][0] = dp[i-1][0] * 9 - dp[i-1][1];
        dp[i][1] = dp[i-1][0];
        dp[i][2] = dp[i-1][2] * 10 + dp[i-1][0] + dp[i-1][1];
    }
}

int solve(int n) {
    int a[10];
    int len = 0;
    while (n) {
        a[++len] = n % 10;
        n/=10;
    }
    a[len + 1] = 0;
    
    int result = 0;
    bool flag = false;
    for (int i = len; i >= 1; i--) {
        int curr = a[i];
        int prev = a[i + 1];
        
        
        if(flag) result += curr * ( dp[i - 1][0] + dp[i - 1][2] );
        else {
            result += curr * dp[i - 1][2];
            if (curr > 4) result += dp[i - 1][0];
            if (curr > 6) result += dp[i - 1][1];
            if (curr > 2 && prev == 6) result += dp[i][1];
            if (curr == 4 ||  (curr == 2 && prev == 6)) {
                result++;
                flag = true;
            }
        }
    }
    return result;
}

int main(int argc, const char * argv[]) {
    genDp();
    
    int m, n;
    
    for (;;){
        
        scanf("%d%d", &m, &n);
        if(m == 0 && n == 0) break;
        printf("%d\n", (n - m + 1) - (solve(n) - solve(m - 1)) );
    }
    
    return 0;
}
