#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct posn {
  int x;
  int y;
};

void freeDDArr(char **DDArr, int n) {
  for(int i=0; i<n; i++) {
    free(DDArr[i]);
  }
  free(DDArr);
}

bool valid_hash_point(struct posn a, int l, char **DDArr) {
  if( a.x<l && a.x>=0 && (a.y == 0 || a.y == 1)) {
    if(DDArr[a.x][a.y] == '#') {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }
}

//Caller must free
struct posn *validate_hash_filter(struct posn *m, int l, int *length,
                                  char **DDArr) {
  int len = 0;
  for(int i=0; i<4; i++) {
    if(valid_hash_point(m[i],l, DDArr)) {
      len++;
    }
  }
  struct posn *n = malloc(len * sizeof(struct posn));
  int count = 0;
  for(int i=0; i<4; i++) {
    if(valid_hash_point(m[i],l, DDArr)) {
      n[count++] = m[i];
    }
  }
  free(m);
  *length=len;
  return n;
}

//Caller must free
struct posn *get_hash_neighbours(struct posn a, int l,
                                 int *length, char **DDArr) {
  struct posn p = {((a.x)+1), (a.y)};
  struct posn q = {((a.x)-1), (a.y)};
  struct posn r = {(a.x), ((a.y)+1)};
  struct posn s = {(a.x), ((a.y)-1)};
  struct posn *ret = malloc(4 * sizeof(struct posn));
  ret[0] = p;
  ret[1] = q;
  ret[2] = r;
  ret[3] = s;
  struct posn *rett = validate_hash_filter(ret, l, length, DDArr);
  return rett;
}


bool CheckSnake(char **DDarr, int n, struct posn start, int hash, int acc) {
  int len;
  for(int j = 0; j<2; j++) {
    for(int k = 0; k<n; k++) {
      printf("%c", DDarr[k][j]);
    }
    printf("\n");
  }
  printf("\n\n");
  struct posn *neigh = get_hash_neighbours(start, n, &len, DDarr);
  DDarr[start.x][start.y] = '@';
  if(len == 0 && acc != hash) {
    free(neigh);
    return false;
  }
  else if (len == 0 && acc == hash) {
    free(neigh);
    return true;
  }
  for(int i = 0; i<len; i++) {
    struct posn NewStart = {neigh[i].x, neigh[i].y};
    char **DDarrTemp = malloc(sizeof(char *) * n);
    for(int j=0; j<n; j++) {
      DDarrTemp[j] = malloc(sizeof(char) * 2);
    }
    for(int j = 0; j<n; j++) {
      for(int k = 0; k<2; k++) {
        DDarrTemp[j][k] = DDarr[j][k];
      }
    }
    if(CheckSnake(DDarrTemp, n, NewStart, hash, acc+1)) {
      freeDDArr(DDarrTemp,n);
      free(neigh);
      return true;
    }
    freeDDArr(DDarrTemp,n);
  }
  free(neigh);
  return false;
}

int main(void) {

  int T;
  scanf("%d",&T);

  for(int i = 0; i<T; i++) {
    int hash = 0;
    int n;
    bool flag = false;
    scanf("%d",&n);
    char **DDarr = malloc(sizeof(char *) * n);
    for(int j=0; j<n; j++) {
      DDarr[j] = malloc(sizeof(char) * 2);
    }
    for(int j=0;j<2;j++) {
      for(int k=0; k<n; k++) {
        scanf(" %c", &(DDarr[k][j]));
        if(DDarr[k][j] == '#') {
          hash++;
        }
      }
    }
    for(int k=0; k<n; k++) {
      if(flag) { break;}
      if(DDarr[k][0] == '#') {
        struct posn start;
        start.x = k;
        start.y = 0;
        char **DDarrTempmain = malloc(sizeof(char *) * n);
        for(int j=0; j<n; j++) {
          DDarrTempmain[j] = malloc(sizeof(char) * 2);
        }
        for(int y = 0; y<n; y++) {
          for(int z = 0; z<2; z++) {
            DDarrTempmain[y][z] = DDarr[y][z];
          }
        }
        if(CheckSnake(DDarrTempmain, n, start, hash, 1)) {
          flag=true;
          freeDDArr(DDarrTempmain, n);
          break;
        }
        freeDDArr(DDarrTempmain, n);
      }
      if(DDarr[k][1] == '#') {
        struct posn start;
        start.x = k;
        start.y = 1;
        char **DDarrTempmain = malloc(sizeof(char *) * n);
        for(int j=0; j<n; j++) {
          DDarrTempmain[j] = malloc(sizeof(char) * 2);
        }
        for(int y = 0; y<n; y++) {
          for(int z = 0; z<2; z++) {
            DDarrTempmain[y][z] = DDarr[y][z];
          }
        }
        if(CheckSnake(DDarrTempmain, n, start, hash, 1)) {
          flag=true;
          freeDDArr(DDarrTempmain, n);
          break;
        }
        freeDDArr(DDarrTempmain, n);
      }
    }
    if(flag) {
      printf("yes\n\n\n");
    }
    else {
      printf("no\n\n\n");
    }
    freeDDArr(DDarr, n);
  }
}
