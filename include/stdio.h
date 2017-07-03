typedef struct {
	int fd;
	unsigned long pos;

	char mode;
} FILE;

static const FILE stdout = {
	.fd = 0,
	.pos = 0,
};

static const FILE stdin = {
	.fd = 1,
	.pos = 0,
};

static const FILE stderr = {
	.fd = 2,
	.pos = 0,
};
