#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


void CommentKiller(FILE* dxrtyc0de, FILE* res) {
	char prevprevprevChar = 0;
	char prevprevChar = 0;
	char prevChar = 0;
	char currentChar = 0;
	int FlagText1 = 0;
	int FlagText2 = 0;
	int FlagCode = 1;
	int FlagComment = 0;
	int FlagBigDig = 0;
	while (!feof(dxrtyc0de)) {
		prevprevprevChar = prevprevChar;
		prevprevChar = prevChar; //писька
		prevChar = currentChar;
		currentChar = fgetc(dxrtyc0de);
		if (FlagCode == 1) {
			if (currentChar == '/' && prevChar == '/') {
				FlagCode = 0;
				FlagComment = 1;
			}
			if (currentChar == '*' && prevChar == '/') { /* _ */
				FlagCode = 0;
				FlagBigDig = 1;
				currentChar = 0;
				prevChar = 0;
			}
			if (prevChar == '"') {
				FlagCode = 0;
				FlagText2 = 1;
			}
			if (prevChar == '\'') {
				FlagCode = 0;
				FlagText1 = 1;
			}
			if (prevChar != '\0' && FlagComment == 0 && FlagBigDig == 0) {
				fprintf(res, "%c", prevChar);
			}
			
		}
		else if (FlagCode != 1) {
			if (FlagComment == 1) {
				if (currentChar == '\n' && prevChar != '\\') {
					FlagComment = 0;
					FlagCode = 1;

				}
				 
			}
			else if (FlagBigDig == 1) {
				if (currentChar == '/' && prevChar == '*') {
					FlagBigDig = 0;
					FlagCode = 1;
					currentChar = 0;
				}
			}
			else if (FlagText1 == 1) {
				fprintf(res, "%c", prevChar);
				if (prevChar == '\'') {
					if (prevprevChar == '\\') {
						if (prevprevprevChar == '\\') {
							FlagCode = 1;
							FlagText1 = 0;
						}
					}
					else {
						FlagCode = 1;
						FlagText1 = 0;
					}
				}
			}
			else if (FlagText2 == 1) {
				fprintf(res, "%c", prevChar);
				if (prevChar == '"') {
					if (prevprevChar == '\\') {
						if (prevprevprevChar == '\\') {
							FlagCode = 1;
							FlagText2 = 0;
						}
					}
					else {
						FlagCode = 1;
						FlagText2 = 0;
					}
				}
			}
			
		}
	}
}


void main() {
	FILE* project, * file, *result;
	project = fopen("project.txt", "r");

	
	int n;
	fscanf(project,"%d\n",&n);

	
	for (int i = 0; i < n; i++) {
		char name[35] = { '\0' };
		fgets(name, 35, project);
		if (name[strlen((const char*)name) -1] == '\n'){
			name[strlen((const char*)name) - 1] = '\0';
		}
		file = fopen((const char *)name, "r");
		char NewName[36] = { '\0' };
		strcpy(NewName, name);
		int lenth = strlen((const char*)NewName) - 1;
		NewName[lenth] = 'w';
		NewName[lenth+1] = 'c';
		NewName[lenth + 2] = '\0';
		result = fopen((const char *)NewName, "w");

		CommentKiller(file, result);
		fclose(file);
		fclose(result);
	}
	fclose(project);
    fprintf("input1.wc",result,"w");
}