#include "server.h"

void create_student_records(struct lab4_q1 *records) {
  struct lab4_q1 one = {
    .id = 1,
    .regno = "160953104",
    .name = "guy no 1",
    .address = "chembur, mumbai",
    .dept = "ict",
    .sem = 6,
    .section = 'b',
    .course_codes_length = 3,
    .course_codes = {
      111,
      222,
      333,
    }
  };

  struct lab4_q1 two = {
    .id = 2,
    .regno = "170911222",
    .name = "guy no 2",
    .address = "somewhere in hyderabad",
    .dept = "mech",
    .sem = 5,
    .section = 'c',
    .course_codes_length = 4,
    .course_codes = {
      111,
      222,
      333,
      444,
    }
  };

  struct lab4_q1 three = {
    .id = 3,
    .regno = "180953126",
    .name = "guy no 3",
    .address = "somewhere in delhi",
    .dept = "ict",
    .sem = 2,
    .section = 'j',
    .course_codes_length = 3,
    .course_codes = {
      111,
      222,
      333,
    }
  };

  struct lab4_q1 four = {
    .id = 4,
    .regno = "160905424",
    .name = "guy no 4",
    .address = "somewhere outside india",
    .dept = "cse",
    .sem = 6,
    .section = 'd',
    .course_codes_length = 4,
    .course_codes = {
      111,
      222,
      333,
      444,
    }
  };

  struct lab4_q1 five = {
    .id = 5,
    .regno = "170912311",
    .name = "guy no 5",
    .address = "assam",
    .dept = "civ",
    .sem = 6,
    .section = 'c',
    .course_codes_length = 3,
    .course_codes = {
      111,
      222,
      333,
    }
  };

  records[0] = one;
  records[1] = two;
  records[2] = three;
  records[3] = four;
  records[4] = five;
}

int get_course_count(struct lab4_q1 *records, int len) {
  int total = 0;
  for(int i = 0; i < len; i++) {
    total += records[i].course_codes_length;
  }
  return total;
}

void create_course_records(struct marks *records, struct lab4_q1 *students, int num_students) {
  int max_marks = 100;
  int marks_i = 0;

  for(int i = 0; i < num_students; i++) {
    for(int j = 0; j < students[i].course_codes_length; j++) {
      struct marks m = {
        student_id:  i,
        course_id: students[i].course_codes[j],
        marks: random() % (max_marks + 1)
      };

      records[marks_i++] = m;
    }
  }
}

int find_student_by_id(struct lab4_q1 *records, int records_length, char *regno) {
  for(int i = 0; i < records_length; i++)
    if(!strcmp(records[i].regno, regno)) 
      return i;
  return -1;
}

int find_marks(struct marks *records, int marks_length, int student_id, int course_id) {
  for(int i = 0; i < marks_length; i++)
    if(records[i].student_id == student_id && records[i].course_id == course_id)
      return records[i].marks;
  return -1;
}

/* FOR DNS SERVER */

void mock_ip_address(char *ip_addr) {
  int a = random() % 256;
  int b = random() % 256;
  int c = random() % 256;
  int d = random() % 256;
  sprintf(ip_addr, "%d.%d.%d.%d", a, b, c, d);
}

void create_dns_records(struct dns_map *records) {
  strcpy(records[0].domain, "www.google.com");
  mock_ip_address(records[0].ip_addr);
  strcpy(records[1].domain, "www.facebook.com");
  mock_ip_address(records[1].ip_addr);
  strcpy(records[2].domain, "www.youtube.com");
  mock_ip_address(records[2].ip_addr);
  strcpy(records[3].domain, "www.gmail.com");
  mock_ip_address(records[3].ip_addr);
  strcpy(records[4].domain, "www.w3schools.com");
  mock_ip_address(records[4].ip_addr);
}

void find_ip_by_domain(struct dns_map* records, int records_len, char *domain, char *result) {
  for(int i = 0; i < records_len; i++) {
    if(!strcmp(records[i].domain, domain)) {
      strcpy(result, records[i].ip_addr);
      return;
    }
  }
  strcpy(result, "Not found.");
}