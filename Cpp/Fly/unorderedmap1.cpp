/* http://blog.csdn.net/hk2291976/article/details/51037095#12-hashtable%E5%92%8Cbucket
 * http://www.cplusplus.com/reference/unordered_map/unordered_map/bucket_count/
 */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main ()
{
    unordered_map<string,string> mymap =
    {
        {"house","maison"},
        {"apple","pomme"},
        {"tree","arbre"},
        {"book","livre"},
        {"door","porte"},
        {"grapefruit","pamplemousse"}
    };
    /************begin和end迭代器***************/
    cout << "mymap contains:";
    for ( auto it = mymap.begin(); it != mymap.end(); ++it )
        cout << " " << it->first << ":" << it->second;
    cout << endl;
    /************bucket操作***************/
     unsigned n = mymap.bucket_count();

    cout << "mymap has " << n << " buckets.\n";

    for (unsigned i=0; i<n; ++i)
    {
        cout << "bucket #" << i << "'s size:"<<mymap.bucket_size(i)<<" contains: ";
        for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
            cout << "[" << it->first << ":" << it->second << "] ";
        cout << "\n";
    }

    cout <<"\nkey:'apple' is in bucket #" << mymap.bucket("apple") <<endl;
    cout <<"\nkey:'computer' is in bucket #" << mymap.bucket("computer") <<endl;

    cout << mymap["house"] << '\n';

    return 0;
}
