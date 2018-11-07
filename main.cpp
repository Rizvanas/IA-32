#include <iostream>

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cout << "Missing parameter\n";
		return 1;
	}

	char *str = _strdup(argv[1]);
	unsigned char *binStr{ nullptr };
	unsigned int strLength{ static_cast<unsigned int>(strlen(argv[1])) };
	unsigned int binStrLength{ strLength * 8 };
	binStr = new unsigned char[binStrLength + 1]; // Labas -> 01001100 01100001 01100010 01100001 01110011\0
	int index{ 0 };

	_asm {
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi
		push cx

		mov eax, str
		mov ecx, [strLength]

		mov esi, eax			// rodo i str pradzia
		add eax, ecx			// sudeda str pradzia su ilgiu, kad butu gauta pabaiga
		mov edi, eax	 	    // rodo i str pabaiga
		lea eax, binStr			// eax dabar rodo i binStr pradzia
		
		for_loop:

			cmp esi, edi
			je exit_loop
			mov dl, [esi]
			mov bx, 0

				toBin:
					cmp bx, 8
					je exit_loop2
					mov cl, 0
					rcr dl, 1
					adc cl, 0
					mov edx, index
					movzx ecx, cl
					inc bx
					inc index
				jmp toBin
				exit_loop2:
			inc esi

		jmp for_loop
		exit_loop:
		
		pop cx
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

	for (size_t i = 0; i < binStrLength; ++i) {
		std::cout << *(binStr + i);
		if (i % 8 == 0) {
			std::cout << " ";
		}
	}

	delete[] binStr;
	binStr = nullptr;

	return 0;
}
