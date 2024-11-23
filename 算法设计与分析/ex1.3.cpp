#include<bits/stdc++.h>
using namespace std;
int dfs( char* s, int l, int r, int k)
{
int cnt[26];
memset(cnt, 0, sizeof(cnt) );
for (int i = l; i <= r; i++) {cnt[s[i] - 'a' ]++;}
char split = 0;
for (int i = 0; i < 26; i++)
{
    if ( cnt[i] > 0 && cnt[i] < k )
    {
    split = i + 'a';
    break;
    }
}
if ( split == 0 )
{
return r - l + 1;
}
int i = l;
int ret = 0;
while (i <= r)
{
    while (i <= r && s[i] == split) {i++;}
    if (i > r) {break;}
    int start = i;
    while  (i <= r && s[i] != split) {i++;}
    int length = dfs(s, start, i-1,k );
    ret = fmax (ret, length );
}
    return ret;
}
int longestSubstring( char* s, int k)
{
return dfs( s, 0, strlen(s) - 1,k);
}
int main()
{
    string c;
    int k,ans;
    cin>>c;
    char* p=(char*)c.data();
    cin>>k;
    ans=longestSubstring(p,k);
    printf("%d",ans);
    return 0;
}
