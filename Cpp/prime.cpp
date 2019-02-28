/*
作者：池筱沫
链接：https://www.zhihu.com/question/29580448/answer/45235320
来源：知乎
著作权归作者所有，转载请联系作者获得授权。

线性筛法：
一边生成质数表，一边删掉每个数的质数倍。复杂度顾名思义，O(N)
*/

#include <cstdio>
#include <vector>
using namespace std;

const long long N = 1000000000;

// 默认为0，即false，表示质数。
bool sieve[N];

long long linear_sieve() {
    vector<int> prime;

    for( int i = 2; i < N; i++ ) {
        if( !sieve[i] ) prime.push_back( i );

        for( int j = 0; i * prime[j] < N; j++ ) {
            //设为true，表示是合数。
            sieve[i * prime[j]] = true;

            if( i % prime[j] == 0 ) break;
        }
    }

    long long sum = 0;

    for( int i = 0; i < ( int )prime.size(); ++i ) {
        sum += prime[i];
    }
    return sum;
}

int main( void ) {
    printf( "%lld", linear_sieve() );
    return 0;
}