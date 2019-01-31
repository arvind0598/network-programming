#include "../server.h"

void print_student_details(struct lab4_q1 student) {
  printf("\nStudent details:\n");
  printf("Name: %s\n", student.name);
  printf("Address: %s\n", student.address);
  printf("Studying in %s %d %c\n", student.dept, student.sem, student.section);
  printf("Enrolled courses are:\n");
  for(int i = 0; i < student.course_codes_length; i++) {
    printf("%d ", student.course_codes[i]);
  }
  printf("\n");
}

int main() {

  // setup database

  struct lab4_q1 *students = malloc(5 * sizeof(struct lab4_q1));
  create_student_records(students);

  int student_marks_size = get_course_count(students, 5);
  
  struct marks *student_marks = malloc(student_marks_size * sizeof(struct marks));
  create_course_records(student_marks, students, 5);

  // setup socket connection

  char buffer[BUFF_SIZE];
  int sockfd = socket_tcp_default();
  SA_IN server = sa_server_default();
  bind_s(sockfd, (SA*)&server, sizeof(server));
  listen_s(sockfd, 1);

  SA_IN client;
  int client_len = sizeof(client);
  int clientfd = accept_s(sockfd, (SA*)&client, &client_len);

  // accept registration number

  server_read_str(clientfd, sockfd, buffer);
  int pos = find_student_by_id(students, 5, buffer);
  struct lab4_q1 student_x;
  if(pos < 0) student_x.id = -1;
  else memcpy(&student_x, &students[pos], sizeof(student_x));
  server_write(clientfd, sockfd, (const void*)&student_x, sizeof(student_x));

  if(pos < 0) error_c2(clientfd, sockfd);

  // accept course code

  int course_code = server_read_int(clientfd, sockfd);
  int marks_x = find_marks(student_marks, student_marks_size, students[pos].id, course_code);
  server_write_int(clientfd, sockfd, marks_x);

  close(clientfd);
  close(sockfd);
  return 0;
}