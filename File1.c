#define _CRT_SECURE_NO_WARNINGS
#define end !feof(file)

#include <stdio.h>
#include <string.h>

int main() {
	FILE *project, *file, *res;
	char name[35], c, b;
	int n = 0;
	int q = 1;
	int k = 1;
	project = fopen("project.txt", "r");
	if (fscanf(project, "%d\n", &n) != NULL) {
		for (int i = 0; i < n; i++) {
			fgets(name, 35, project);
			for (int j = strlen(name); j >= 0; j--)
				if (name[j] == '\n') {
					name[j] = '\0';
					break;
				}
			file = fopen(name, "r");

			for (int j = strlen(name); j >= 0; j--) {
				if (name[j] == '.') {
					name[j + 1] = 'w';
					name[j + 2] = 'c';
					name[j + 3] = '\0';
					break;
				}
			}
			res = fopen(name, "w");
			if (res != NULL) {
				while (end) {
					q = 1;
					c = fgetc(file);
					if (end) {
						if (c == '/') {
							b = fgetc(file);
							if (b == '*') {
								b = fgetc(file);
								while (end) {
									if (b == '*') {
										b = fgetc(file);

										if (b == '/') {k++;	break;}
									}
									if (b == '*') continue;
									b = fgetc(file);
								}

								if (feof(file)) break;
								if (k != 1) {k = 1;	continue;}
							}
							if (b == '/') {
								while (end) {
									b = fgetc(file);
									while (b == '\\') {
										b = fgetc(file);
										if (b == '\n') {
											fputc(b, res);
											b = fgetc(file);
											continue;
										}
									}
									if (b == '\n') {
										if (end) {fputc(b, res); break;}
									}
								}
							}
							else {
								fputc(c, res);
								c = b;
							}
						}
						if (c == '\'') {
							if (end) fputc(c, res);
							while (end) {
								c = fgetc(file);
								if (end) fputc(c, res);
								while (c == '\\') {
									q++;
									c = fgetc(file);
									if (end) fputc(c, res);
									if ((q > 1) && (q % 2 == 0) && c == '\'') break;
								}
								if ((q % 2 != 0) && (c == '\'')) break;
								if (c == '\n') break;
								q = 1;
							}
						}
						if (c == '\"') {
							if (end) fputc(c, res);
							while (end) {
								c = fgetc(file);
								if (end) fputc(c, res);
								if (c == '\"') break;
								if (c == '\n') break;
								while (c == '\\') {
									q++;
									c = fgetc(file);
									if ((q % 2 != 0) && (c == '\n')) break;
									if (end) fputc(c, res);
									if ((q % 2 == 0) && (c == '\"')) break;
								}
								if ((q % 2 != 0) && (c == '\"')) break;
								if ((q % 2 != 0) && (c == '\n')) break;
								q = 1;
							}
						}
						if ((end && c != '\"') && (c != '\'') && (c != '/')) {fputc(c, res); continue;}
					}
				}
			}
		}
	}
	else return -1;
	fclose(project);
	return 0;
}

