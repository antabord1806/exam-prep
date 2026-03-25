#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;


node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int accept(char **s, char c)
{
    if (**s)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

node    *parse_group_or_number(char **s);
node    *parse_addition(char **s);
node    *parse_mult(char **s);

node    *parse_group_or_number(char **s)
{
    node    *res;
    node    tmp;

    if (**s == '(')
    {
        (*s)++;
        res = parse_addition(s);
        if (!res || **s != ')')
        {
            destroy_tree(res);
            unexpected(**s);
            return NULL;
        }
        (*s)++;
        return res;
    }
    if (isdigit(**s))
    {
        tmp.type = VAL;
        tmp.val = **s - '0';
        res = new_node(tmp);
        (*s)++;
        return res;
    }
    unexpected(**s);
    return NULL;
}

node    *parse_mult(char **s)
{
    node *right;
    node *left;
    node tmp;

    left = parse_group_or_number(s);
    if (!left)
        return NULL;
    while(**s == '*')
    {
        (*s)++;
        right = parse_group_or_number(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        tmp.type = MULTI;
        tmp.r = right;
        tmp.l = left;
        left = new_node(tmp);
    }
    return left;
}

node    *parse_addition(char **s)
{
    node *right;
    node *left;
    node tmp;

    left = parse_mult(s);
    if (!left)
        return NULL;
    while (**s == '+')
    {
        (*s)++;
        right = parse_mult(s);
        if (!right)
        {
            destroy_tree(left);
            return NULL;
        }
        tmp.l = left;
        tmp.r = right;
        tmp.type = ADD;
        left = new_node(tmp);
    }
    return left;
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int argc, char **argv)
{
    char *p;

    if (argc != 2)
        return (1);
    p = argv[1];
    node *tree = parse_addition(&p);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    if (*p != '\0')
    {
        unexpected('\0');
        destroy_tree(tree);
        return 1;
    }
    destroy_tree(tree);
    return 0;
}