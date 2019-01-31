#include "../lab.h"

struct marks {
  int student_id;
  int course_id;
  int marks;
};

void create_student_records(struct lab4_q1 *records);
void create_course_records(struct marks *records, struct lab4_q1 *students, int num_students);
int get_course_count(struct lab4_q1 *records, int len);
int find_student_by_id(struct lab4_q1 *records, int records_length, char *regno);
int find_marks(struct marks *records, int records_length, int student_id,int course_id);

struct dns_map {
  char ip_addr[30];
  char domain[30];
};

void create_dns_records(struct dns_map *records);
void find_ip_by_domain(struct dns_map *records, int records_len, char *domain, char *result);