## Description

Devine Sweetmelon Agency (a.k.a. DSA) is an internationally renowned group company selling sweet melons. Based on credible sources, DSA comprises $N$ companies, numbered from $1$ to $N$, where the company numbered $1$ is the topmost company in DSA. The organizational structure of DSA is quite straightforward: the $i$-th company, except the topmost company, has exactly one parent company $x_i$.

Chicken-Soup has a strong liking for sweet melons and desires to eat as many sweet melons as possible. To achieve this goal, Chicken-Soup conducts an investigation and obtains the sales plans of DSA for the next $M$ days. According to the sales plans, every day, each company in DSA will launch a sales event that lasts for several days. Specifically, the sales event of company $i$ on day $j$ would offer sweet melons at a price of $c_{ij}$ dollars and will last for $d_{ij}$ days. This implies that Chicken-Soup can purchase sweet melons at the price of $c_{ij}$ on day $j$, $j + 1$, $\dots$, $j + d_{ij}$.

In order to simplify the purchase process, Chicken-Soup decides to sign a contract with exactly one company in DSA every day. The contract requires ze to buy exactly one sweet melon from the contracting company and each of its offspring companies on the same day. However, despite wanting to purchase all the sweet melons, Chicken-Soup's daily pocket money is limited to $C$ dollars. In addition, Chicken-Soup cannot carry over the daily pocket money to the next day. Given the constraint, can you help calculate the maximum number of sweet melons that Chicken-Soup can purchase each day?

## Input

The first line contains three space-separated integers $N, M$, and $C$, which are the number of companies, the length of sales events, and Chiken-Soup's daily pocket money, respectively.

The second line contains $N-1$ space-separated integers $x_2, x_3, \ldots, x_N$, where $x_i$ represents the parent company of company $i$.

The next input lines can be divided into $M$ parts, each representing the sales plan on the $j$-th day for $j = 1, 2, \ldots, M$.

Each part contains $N$ lines, and the $i$-th line of the $j$-th part contains two space-separated integers $c_{ij}, d_{ij}$, which are the price and the length of the sales plan of company $i$ on day $j$.

## Output

The output should consist of $M$ lines, and the $j$-th line should be the maximum number of sweet melons that Chicken-Soup can purchase on day $j$.

## Constraint

- $1 \le NM \le 10^6$
- $1 \le C \le 10^9$
- $1 \le x_i \le N$
- $0 \le d_{ij} \le M$
- $0 \le c_{ij} \le C$

### Subtask 1 (10pts)

- $1\le NM \le 10^3$

### Subtask 2 (15pts)

- $x_i = i - 1, i \in \lbrace 2, 3, \dots, N\rbrace$

### Subtask 3 (15pts)

- $d_{ij} = M$

### Subtask 4 (60pts)

No other constraint

## Sample Testcases

### Sample Input 1

```
5 3 10
1 1 2 2
10 2
1 1
2 2
1 2
8 2
1 2
10 2
1 0
2 1
1 0
5 2
5 1
9 2
3 0
10 1
```

### Sample Output 1

```
3
5
1
```

### Sample Input 2

```
4 4 20
1 2 3
5 4
10 4
15 4
20 4
20 4
5 4
10 4
15 4
15 4
20 4
5 4
10 4
10 4
15 4
20 4
5 4
```

### Sample Output 2
```
1
1
3
4
```

## Hint

Here are the details of sample 1:

The organization graph of DSA is:

![](https://i.imgur.com/iwjpKgn.png)

The following table shows the price of sweet melons sold by each company every day.

<style>
table {
    border-collapse: collapse;
}
table, th, td {
   border: 1px solid white;
}
blockquote {
    border-left: solid blue;
    padding-left: 10px;
}
</style>

| company | day 1 | day2  | day 3    |
| ------- | ----- | ----- | -------- |
| 1       | 10    | 10, 1 | 10, 1, 5 |
| 2       | 1     | 1, 10 | 10, 5    |
| 3       | 2     | 2, 1  | 2, 9     |
| 4       | 1     | 1, 2  | 1, 2, 3  |
| 5       | 8     | 8, 1  | 8, 10    |

On the first day, Chicken-Soup can sign a contract with company $2$ and buy sweet melons at prices $1, 1, 8$ from companies $2, 4, 5$ respectively.

On the second day, Chicken-Soup can sign a contract with company $1$ and buy sweet melons at prices $1, 1, 2, 2, 1$ from companies $1, 2, 3, 4, 5$ respectively.

On the third day, Chicken-Soup can sign a contract with company $5$ and buy one sweet melon at price $8$ from company $5$.
