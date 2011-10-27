int r[12];
int m[1200];

main() {
    int i=0;
    int pc=0;
    int instr;
    while( scanf( "%u ", &m[i++] ) == 1 );
    for(instr=1;;instr++)
    switch( m[pc]/100 ) {
    case 1:
	printf( "%u\n", instr );
	exit(0);
    case 2:
	r[m[pc]/10-20] = m[pc]%10;
	r[m[pc]/10-20] %= 1000;
	pc++;
	break;
    case 3:
	r[m[pc]/10-30] += m[pc]%10;
	r[m[pc]/10-30] %= 1000;
	pc++;
	break;
    case 4:
	r[m[pc]/10-40] *= m[pc]%10;
	r[m[pc]/10-40] %= 1000;
	pc++;
	break;
    case 5:
	r[m[pc]/10-50] = r[m[pc]%10];
	pc++;
	break;
    case 6:
	r[m[pc]/10-60] += r[m[pc]%10];
	r[m[pc]/10-60] %= 1000;
	pc++;
	break;
    case 7:
	r[m[pc]/10-70] *= r[m[pc]%10];
	r[m[pc]/10-70] %= 1000;
	pc++;
	break;
    case 8:
	r[m[pc]/10-80] = m[r[m[pc]%10]];
	pc++;
	break;
    case 9:
	m[r[m[pc]%10]] = r[m[pc]/10-90] ;
	pc++;
	break;
    case 0:
	if( r[m[pc]%10] ) pc = r[m[pc]/10];
	else pc++;
	break;
    }
}

