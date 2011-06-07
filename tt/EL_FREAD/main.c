#include <stdio.h>
#include <stdlib.h>
#include <elf_struct.h>

int main(int argc, char **argv) {
	FILE *f, *f_out;
	Elf32_Ehdr header;
	Elf32_Shdr *sections;
	int i, t = 0, t_min = 0, t_zero = 0;;
	char *read;
	if(argc <= 1)
		return;
	
	f = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");

	fread((void *)&header, sizeof(header), 1, f);
	
	sections = malloc(header.e_shnum * sizeof(Elf32_Shdr));
	fseek(f, (long)header.e_shoff, SEEK_SET);

	for(i = 0; i < header.e_shnum; i++) {
		fread((void *)&sections[i], sizeof(Elf32_Shdr), 1, f);
		if( t < sections[i].sh_addr )
			t = sections[i].sh_addr;
	}
	
	if(argc == 4 && strcmp(argv[3],"-nonzero") == 0) {
		t_min = t;
		for(i = 0; i < header.e_shnum; i++) {
			if(t_min > sections[i].sh_addr && sections[i].sh_addr != 0)
				t_min = sections[i].sh_addr;
		}
	}
	
	t_zero = t - t_min;
	for(i = 0; i < t_zero; i++)
		fwrite("\0", sizeof(char), 1, f_out);

	for(i = 0; i < header.e_shnum; i++)
		if( sections[i].sh_addr != 0 ) {
			fseek(f, (long)sections[i].sh_offset, SEEK_SET);
			read = malloc(sections[i].sh_size * sizeof(char));
			fread((void *)read, sections[i].sh_size, 1, f);
			fseek(f_out, (long) (sections[i].sh_addr - t_min) , SEEK_SET);
			fwrite(read, sizeof(char), sections[i].sh_size, f_out);
		}

	/*printf("HEADER %d:\n%x\n%x\n%x\n%x\n%x\n%x\n%x\n%x\n%x\n%x\n", i,
	sections[i].sh_name, sections[i].sh_type, sections[i].sh_flags, sections[i].sh_addr, sections[i].sh_offset, 
	sections[i].sh_size, sections[i].sh_link, sections[i].sh_info, sections[i].sh_addralign, sections[i].sh_entsize);*/
	
	/*printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
	header.e_type, header.e_machine, header.e_version, header.e_entry, header.e_phoff, header.e_shoff,
	header.e_flags, header.e_ehsize, header.e_phentsize, header.e_phnum, header.e_shentsize, header.e_shnum, header.e_shstrndx);*/


	fclose(f);
	fclose(f_out);
	
	return 0;
}
