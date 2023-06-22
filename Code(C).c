#include <stdio.h>
#include <stdlib.h>

struct task {
  int l_cost, cost, r_cost, total_cost;
  int time, max_over;
  struct task *l, *r;
};

void update_task(struct task *t) {
  int cur_over, max_over;
  max_over = t->cost - t->time;
  if (t->l) {
    t->l_cost = t->l->total_cost;
    max_over += t->l_cost;
    cur_over = t->l->max_over;
    if (cur_over > max_over) max_over = cur_over;
  } else {
    t->l_cost = 0;
  }
  if (t->r) {
    t->r_cost = t->r->total_cost;
    cur_over = t->r->max_over + t->l_cost + t->cost;
    if (cur_over > max_over) max_over = cur_over;
  } else {
    t->r_cost = 0;
  }
  t->total_cost = t->l_cost + t->cost + t->r_cost;
  t->max_over = max_over;
}

struct task *new_task(int time, int cost) {
  struct task *t;
  t = malloc(sizeof(struct task));
  t->l = t->r = 0;
  t->time = time;
  t->cost = cost;
  update_task(t);
  return t;
}

void free_task(struct task *t, int recur) {
  if (t) {
    if (recur) {
      free_task(t->l, recur);
      free_task(t->r, recur);
    }
    free(t);
  }
}

void insert_task(struct task **tree, struct task *t) {
  struct task *cur_task, **next_tree;
  if (cur_task = *tree) {
    next_tree = (t->time < cur_task->time) ? &(cur_task->l) : &(cur_task->r);
    insert_task(next_tree, t);
    update_task(cur_task);
  } else {
    *tree = t;
  }
}

int main(void) {
  int i, num_tasks, task_due, task_minutes;
  struct task *tree = 0;
  scanf("%d", &num_tasks);
  for (i = 0; i < num_tasks; ++i) {
    scanf("%d %d", &task_due, &task_minutes);
    insert_task(&tree, new_task(task_due, task_minutes));
    printf("%d\n", tree->max_over >= 0 ? tree->max_over : 0);
  }
  free_task(tree, 1);
  return 0;
}