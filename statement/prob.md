## Description

Devine Sweetmelon Agency (a.k.a. DSA) is an internationally renowned group company selling sweet melons. According to reliable sources, DSA is composed of $N$ companies, numbered $1$ to $N$, and the company numbered $1$ is the leading company in DSA. The organization of DSA is very clear, each company in DSA except the leading company has exactly one parent company, where the company numbered $i$ has a parent company numbered $x_i$.

Chicken-Soup likes to eat sweet melon at most. To eat as many sweet melons as ze can, ze investigated and obtained the sales plans of DSA for the next $M$ days. According to the sales plans, every day, each company in DSA will launch a sales event that lasts for several days. Where the sales event of the company $i$ launched on the day $j$ is to offer sweet melon at price $c_{ij}$, and will be held in the following $d_{ij}$ days. Which means Chicken-Soup can buy a sweet melon at price $c_{ij}$ on day $j, j + 1, \dots, j + d_{ij}$.

To simplify the purchase process, Chicken-Soup decided to sign a contract with exactly one company in DSA every day. The contract required that ze must buy exactly one sweet melon from the contracting company and each of its offspring companies on the same day. Although ze wants to buy all the sweet melons, the daily pocket money for Chicken-Soup is only $C$ dollars. Note that Chicken-Soup can't preserve daily pocket money to next day. Can you help him calculate how many sweet melons ze can eat at most every day?

## Input

The first line contains three integers $N, M$ and $C$ - - the company counts in DSA, the length of sales plan Chicken-Soup obtained, and Chicken-Soup's daily pocket money.

The second line contains $N-1$ integers $x_2$ to $x_N$, $x_i$ represents the parent company of the company $i$

The following input contains $M$ part, and the $j$-th part represents the data of $j$-th day.

Each part contains $N$ lines, and the $i$-th line of $j$-th part contains two integer $c_{ij}, d_{ij}$ - - the data of sales event of the company $i$ on day $j$

## Output

The output should consist of $M$ lines.

The $i$-th line should be the number of sweet melon Chicken-Soup can eat at most on day $i$.

## Constraint

- $1 \le NM \le 10^6$
- $1 \le C \le 10^9$
- $1 \le x_i \le N$
- $0 \le d_{ij} \le M$
- $0 \le c_{ij} \le C$

### Subtask 1 (10pts)

- $1\le NM \le 10^3$

### Subtask 2 (15pts)

- $x_i = i - 1, i \in \{2, 3, \dots, N\}$

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

## Hint

Here are the details of sample 1:

The organization graph of DSA is:

![](https://i.imgur.com/iwjpKgn.png)

And the following table shows the price of sweet melons sold by each company every day.

```
| company | day 1 | day2  | day 3    |
| ------- | ----- | ----- | -------- |
| 1       | 10    | 10, 1 | 10, 1, 5 |
| 2       | 1     | 1, 10 | 10, 5    |
| 3       | 2     | 2, 1  | 2, 9     |
| 4       | 1     | 1, 2  | 1, 2, 3  |
| 5       | 8     | 8, 1  | 8, 10    |
```

The first day, Chicken-Soup can sign a contract with company $2$ and buy sweet melons at prices $1, 1, 8$ from companies $2, 4, 5$ respectively.

The second day, Chicken-Soup can sign a contract with company $1$ and buy sweet melons at prices $1, 1, 2, 2, 1$ from companies $1, 2, 3, 4, 5$ respectively.

The third day, Chicken-Soup can sign a contract with company $5$ and buy sweet melons at price $8$ from company $5$.
