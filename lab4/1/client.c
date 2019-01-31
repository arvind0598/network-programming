#include "../../lab.h"

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
  char buffer[BUFF_SIZE];
  SA_IN server = sa_client_default();
  int sockfd = socket_tcp_default();
  connect_s(sockfd, (SA*)&server, sizeof(server));

  printf("Enter registration number.\n");
  stdin_get_str(buffer);
  client_write_str(sockfd, buffer);

  struct lab4_q1 student;

  client_read(sockfd, (void*)&student, sizeof(student));
  if(student.id == -1) {
    printf("The student does not exist.\n");
    error_c(sockfd);
  }
  
  print_student_details(student);

  int course;
  printf("Enter a course number.\n");
  scanf("%d", &course);
  client_write_int(sockfd, course);

  int marks = client_read_int(sockfd);
  if(marks < 0) printf("%s has not enrolled for this course.\n", student.name);
  else printf("%s has recieved %d in course %d.\n", student.name, marks, course);

  close(sockfd);
  return 0;
}