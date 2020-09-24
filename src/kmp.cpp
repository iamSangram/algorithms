// Knuth–Morris–Pratt algorithm

// The complexity of the table algorithm is O(n), where n is the length of W
//"Partial match" table (also known as "failure function")
void kmp_table(char* W, int* T) {
    // an array of characters, W (the word to be analyzed)
    // an array of integers, T (the table to be filled)
    // pos: the current position we are computing in T
    // cnd: the zero-based index in W of the next character of the current
    // candidate substring
    int pos = 2, cnd = 0;
    T[0] = 0;
    T[1] = 0;
    int lenW = strlen(W);
    while (pos < lenW) {
        // first case: the substring continues
        if (W[pos - 1] == W[cnd]) {
            cnd++;
            T[pos] = cnd;
            pos++;
        }
        // second case: it doesn't, but we can fall back
        else if (cnd > 0) {
            cnd = T[cnd];
        }
        // third case: we have run out of candidates.  Note cnd = 0
        else {
            T[pos] = 0;
            pos++;
        }
    }
    return;
}

// the search portion of the Knuth–Morris–Pratt algorithm has complexity O(n),
// where n is the length of S
int kmp_search(char* S, char* W)
// an array of characters, S (the text to be searched)
// an array of characters, W (the word sought)
{
    int m = 0, i = 0, lenS = strlen(S), lenW = strlen(W);
    if(0 == lenW) {
        return 0; // TODO: should be zero?
    }
    while (m + i < lenS) {
        if (W[i] == S[m + i]) {
            if (i == lenW - 1) return m;  // matched, return the starting point
            i++;
        } else if(i > 0){
            m = m + i - T[i];
            i = T[i];
        }else {
            ++m;
        }
    }
    // if we reach here, we have searched all of S unsuccessfully, return -1
    return -1;
}
