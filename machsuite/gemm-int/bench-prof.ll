; ModuleID = 'bench.ll'
source_filename = "bench.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.stat = type { i32, i16, i16, i64, i32, i32, i32, %struct.timespec, %struct.timespec, %struct.timespec, %struct.timespec, i64, i64, i32, i32, i32, i32, [2 x i64] }
%struct.timespec = type { i64, i64 }
%struct.bench_args_t = type { [4096 x i32], [4096 x i32], [4096 x i32] }

@.str = private unnamed_addr constant [24 x i8] c"Invalid file descriptor\00", align 1
@__func__.readfile = private unnamed_addr constant [9 x i8] c"readfile\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"bench.c\00", align 1
@.str.2 = private unnamed_addr constant [34 x i8] c"fd>1 && \22Invalid file descriptor\22\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"Couldn't determine file size\00", align 1
@.str.4 = private unnamed_addr constant [51 x i8] c"0==fstat(fd, &s) && \22Couldn't determine file size\22\00", align 1
@.str.5 = private unnamed_addr constant [14 x i8] c"File is empty\00", align 1
@.str.6 = private unnamed_addr constant [25 x i8] c"len>0 && \22File is empty\22\00", align 1
@.str.7 = private unnamed_addr constant [14 x i8] c"read() failed\00", align 1
@.str.8 = private unnamed_addr constant [29 x i8] c"status>=0 && \22read() failed\22\00", align 1
@.str.9 = private unnamed_addr constant [23 x i8] c"Invalid section number\00", align 1
@__func__.find_section_start = private unnamed_addr constant [19 x i8] c"find_section_start\00", align 1
@.str.10 = private unnamed_addr constant [33 x i8] c"n>=0 && \22Invalid section number\22\00", align 1
@.str.11 = private unnamed_addr constant [21 x i8] c"Invalid input string\00", align 1
@__func__.parse_int_array = private unnamed_addr constant [16 x i8] c"parse_int_array\00", align 1
@.str.12 = private unnamed_addr constant [34 x i8] c"s!=NULL && \22Invalid input string\22\00", align 1
@.str.13 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@__stderrp = external global %struct.__sFILE*, align 8
@.str.14 = private unnamed_addr constant [35 x i8] c"Invalid input: line %d of section\0A\00", align 1
@.str.15 = private unnamed_addr constant [11 x i8] c"input.data\00", align 1
@.str.16 = private unnamed_addr constant [30 x i8] c"Couldn't open input data file\00", align 1
@__func__.run_benchmark = private unnamed_addr constant [14 x i8] c"run_benchmark\00", align 1
@.str.17 = private unnamed_addr constant [43 x i8] c"in_fd>0 && \22Couldn't open input data file\22\00", align 1
@.str.18 = private unnamed_addr constant [27 x i8] c"One example output is %d \0A\00", align 1
@instructionCounter = common global i64 0
@basicBlockCounter = common global i64 0
@addCounter = common global i64 0
@subCounter = common global i64 0
@mulCounter = common global i64 0
@divCounter = common global i64 0
@remCounter = common global i64 0
@andCounter = common global i64 0
@orCounter = common global i64 0
@xorCounter = common global i64 0
@branchCounter = common global i64 0
@switchCounter = common global i64 0
@storeCounter = common global i64 0
@loadCounter = common global i64 0
@otherCount = common global i64 0
@readfile.glob = common global i64 0
@__assert_rtn.glob = common global i64 0
@"\01_fstat$INODE64.glob" = common global i64 0
@malloc.glob = common global i64 0
@"\01_read.glob" = common global i64 0
@"\01_close.glob" = common global i64 0
@find_section_start.glob = common global i64 0
@parse_int_array.glob = common global i64 0
@strtok.glob = common global i64 0
@strtol.glob = common global i64 0
@fprintf.glob = common global i64 0
@strlen.glob = common global i64 0
@run_benchmark.glob = common global i64 0
@"\01_open.glob" = common global i64 0
@free.glob = common global i64 0
@gemm.glob = common global i64 0
@printf.glob = common global i64 0
@main.glob = common global i64 0
@formatLong = private unnamed_addr constant [27 x i8] c"\0A\0AinstructionCounter: %ld\0A\00", align 1
@formatLong.1 = private unnamed_addr constant [24 x i8] c"basicBlockCounter: %ld\0A\00", align 1
@formatLong.2 = private unnamed_addr constant [17 x i8] c"addCounter: %ld\0A\00", align 1
@formatLong.3 = private unnamed_addr constant [17 x i8] c"subCounter: %ld\0A\00", align 1
@formatLong.4 = private unnamed_addr constant [17 x i8] c"mulCounter: %ld\0A\00", align 1
@formatLong.5 = private unnamed_addr constant [17 x i8] c"divCounter: %ld\0A\00", align 1
@formatLong.6 = private unnamed_addr constant [17 x i8] c"remCounter: %ld\0A\00", align 1
@formatLong.7 = private unnamed_addr constant [17 x i8] c"andCounter: %ld\0A\00", align 1
@formatLong.8 = private unnamed_addr constant [16 x i8] c"orCounter: %ld\0A\00", align 1
@formatLong.9 = private unnamed_addr constant [17 x i8] c"xorCounter: %ld\0A\00", align 1
@formatLong.10 = private unnamed_addr constant [20 x i8] c"branchCounter: %ld\0A\00", align 1
@formatLong.11 = private unnamed_addr constant [20 x i8] c"switchCounter: %ld\0A\00", align 1
@formatLong.12 = private unnamed_addr constant [19 x i8] c"storeCounter: %ld\0A\00", align 1
@formatLong.13 = private unnamed_addr constant [18 x i8] c"loadCounter: %ld\0A\00", align 1
@formatLong.14 = private unnamed_addr constant [17 x i8] c"otherCount: %ld\0A\00", align 1
@formatEmpty = private unnamed_addr constant [3 x i8] c"\0A\0A\00", align 1
@formatLong.15 = private unnamed_addr constant [15 x i8] c"readfile: %ld\0A\00", align 1
@formatLong.16 = private unnamed_addr constant [19 x i8] c"__assert_rtn: %ld\0A\00", align 1
@formatLong.17 = private unnamed_addr constant [22 x i8] c"\01_fstat$INODE64: %ld\0A\00", align 1
@formatLong.18 = private unnamed_addr constant [13 x i8] c"malloc: %ld\0A\00", align 1
@formatLong.19 = private unnamed_addr constant [13 x i8] c"\01_read: %ld\0A\00", align 1
@formatLong.20 = private unnamed_addr constant [14 x i8] c"\01_close: %ld\0A\00", align 1
@formatLong.21 = private unnamed_addr constant [25 x i8] c"find_section_start: %ld\0A\00", align 1
@formatLong.22 = private unnamed_addr constant [22 x i8] c"parse_int_array: %ld\0A\00", align 1
@formatLong.23 = private unnamed_addr constant [13 x i8] c"strtok: %ld\0A\00", align 1
@formatLong.24 = private unnamed_addr constant [13 x i8] c"strtol: %ld\0A\00", align 1
@formatLong.25 = private unnamed_addr constant [14 x i8] c"fprintf: %ld\0A\00", align 1
@formatLong.26 = private unnamed_addr constant [13 x i8] c"strlen: %ld\0A\00", align 1
@formatLong.27 = private unnamed_addr constant [20 x i8] c"run_benchmark: %ld\0A\00", align 1
@formatLong.28 = private unnamed_addr constant [13 x i8] c"\01_open: %ld\0A\00", align 1
@formatLong.29 = private unnamed_addr constant [11 x i8] c"free: %ld\0A\00", align 1
@formatLong.30 = private unnamed_addr constant [11 x i8] c"gemm: %ld\0A\00", align 1
@formatLong.31 = private unnamed_addr constant [13 x i8] c"printf: %ld\0A\00", align 1
@formatLong.32 = private unnamed_addr constant [11 x i8] c"main: %ld\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @readfile(i32) #0 {
  %2 = atomicrmw add i64* @readfile.glob, i64 1 seq_cst
  %3 = alloca i32, align 4
  %4 = alloca i8*, align 8
  %5 = alloca %struct.stat, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i32 %0, i32* %3, align 4
  %9 = load i32, i32* %3, align 4
  %10 = icmp sgt i32 %9, 1
  br i1 %10, label %11, label %12

11:                                               ; preds = %1
  br label %12

12:                                               ; preds = %11, %1
  %13 = phi i1 [ false, %1 ], [ true, %11 ]
  %14 = xor i1 %13, true
  %15 = zext i1 %14 to i32
  %16 = sext i32 %15 to i64
  %17 = icmp ne i64 %16, 0
  br i1 %17, label %18, label %20

18:                                               ; preds = %12
  call void @__assert_rtn(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @__func__.readfile, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 14, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.2, i32 0, i32 0)) #4
  unreachable

19:                                               ; No predecessors!
  br label %21

20:                                               ; preds = %12
  br label %21

21:                                               ; preds = %20, %19
  %22 = load i32, i32* %3, align 4
  %23 = call i32 @"\01_fstat$INODE64"(i32 %22, %struct.stat* %5)
  %24 = icmp eq i32 0, %23
  br i1 %24, label %25, label %26

25:                                               ; preds = %21
  br label %26

26:                                               ; preds = %25, %21
  %27 = phi i1 [ false, %21 ], [ true, %25 ]
  %28 = xor i1 %27, true
  %29 = zext i1 %28 to i32
  %30 = sext i32 %29 to i64
  %31 = icmp ne i64 %30, 0
  br i1 %31, label %32, label %34

32:                                               ; preds = %26
  call void @__assert_rtn(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @__func__.readfile, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 15, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.4, i32 0, i32 0)) #4
  unreachable

33:                                               ; No predecessors!
  br label %35

34:                                               ; preds = %26
  br label %35

35:                                               ; preds = %34, %33
  %36 = getelementptr inbounds %struct.stat, %struct.stat* %5, i32 0, i32 11
  %37 = load i64, i64* %36, align 8
  store i64 %37, i64* %6, align 8
  %38 = load i64, i64* %6, align 8
  %39 = icmp sgt i64 %38, 0
  br i1 %39, label %40, label %41

40:                                               ; preds = %35
  br label %41

41:                                               ; preds = %40, %35
  %42 = phi i1 [ false, %35 ], [ true, %40 ]
  %43 = xor i1 %42, true
  %44 = zext i1 %43 to i32
  %45 = sext i32 %44 to i64
  %46 = icmp ne i64 %45, 0
  br i1 %46, label %47, label %49

47:                                               ; preds = %41
  call void @__assert_rtn(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @__func__.readfile, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 17, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.6, i32 0, i32 0)) #4
  unreachable

48:                                               ; No predecessors!
  br label %50

49:                                               ; preds = %41
  br label %50

50:                                               ; preds = %49, %48
  %51 = load i64, i64* %6, align 8
  %52 = add nsw i64 %51, 1
  %53 = call i8* @malloc(i64 %52) #5
  store i8* %53, i8** %4, align 8
  store i64 0, i64* %7, align 8
  br label %54

54:                                               ; preds = %79, %50
  %55 = load i64, i64* %7, align 8
  %56 = load i64, i64* %6, align 8
  %57 = icmp slt i64 %55, %56
  br i1 %57, label %58, label %83

58:                                               ; preds = %54
  %59 = load i32, i32* %3, align 4
  %60 = load i8*, i8** %4, align 8
  %61 = load i64, i64* %7, align 8
  %62 = getelementptr inbounds i8, i8* %60, i64 %61
  %63 = load i64, i64* %6, align 8
  %64 = load i64, i64* %7, align 8
  %65 = sub nsw i64 %63, %64
  %66 = call i64 @"\01_read"(i32 %59, i8* %62, i64 %65)
  store i64 %66, i64* %8, align 8
  %67 = load i64, i64* %8, align 8
  %68 = icmp sge i64 %67, 0
  br i1 %68, label %69, label %70

69:                                               ; preds = %58
  br label %70

70:                                               ; preds = %69, %58
  %71 = phi i1 [ false, %58 ], [ true, %69 ]
  %72 = xor i1 %71, true
  %73 = zext i1 %72 to i32
  %74 = sext i32 %73 to i64
  %75 = icmp ne i64 %74, 0
  br i1 %75, label %76, label %78

76:                                               ; preds = %70
  call void @__assert_rtn(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @__func__.readfile, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 22, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.8, i32 0, i32 0)) #4
  unreachable

77:                                               ; No predecessors!
  br label %79

78:                                               ; preds = %70
  br label %79

79:                                               ; preds = %78, %77
  %80 = load i64, i64* %8, align 8
  %81 = load i64, i64* %7, align 8
  %82 = add nsw i64 %81, %80
  store i64 %82, i64* %7, align 8
  br label %54

83:                                               ; preds = %54
  %84 = load i8*, i8** %4, align 8
  %85 = load i64, i64* %6, align 8
  %86 = getelementptr inbounds i8, i8* %84, i64 %85
  store i8 0, i8* %86, align 1
  %87 = load i32, i32* %3, align 4
  %88 = call i32 @"\01_close"(i32 %87)
  %89 = load i8*, i8** %4, align 8
  ret i8* %89
}

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #1

declare i32 @"\01_fstat$INODE64"(i32, %struct.stat*) #2

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #3

declare i64 @"\01_read"(i32, i8*, i64) #2

declare i32 @"\01_close"(i32) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @find_section_start(i8*, i32) #0 {
  %3 = atomicrmw add i64* @find_section_start.glob, i64 1 seq_cst
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %5, align 8
  store i32 %1, i32* %6, align 4
  store i32 0, i32* %7, align 4
  %8 = load i32, i32* %6, align 4
  %9 = icmp sge i32 %8, 0
  br i1 %9, label %10, label %11

10:                                               ; preds = %2
  br label %11

11:                                               ; preds = %10, %2
  %12 = phi i1 [ false, %2 ], [ true, %10 ]
  %13 = xor i1 %12, true
  %14 = zext i1 %13 to i32
  %15 = sext i32 %14 to i64
  %16 = icmp ne i64 %15, 0
  br i1 %16, label %17, label %19

17:                                               ; preds = %11
  call void @__assert_rtn(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @__func__.find_section_start, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 33, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.10, i32 0, i32 0)) #4
  unreachable

18:                                               ; No predecessors!
  br label %20

19:                                               ; preds = %11
  br label %20

20:                                               ; preds = %19, %18
  %21 = load i32, i32* %6, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %23, label %25

23:                                               ; preds = %20
  %24 = load i8*, i8** %5, align 8
  store i8* %24, i8** %4, align 8
  br label %71

25:                                               ; preds = %20
  br label %26

26:                                               ; preds = %58, %25
  %27 = load i32, i32* %7, align 4
  %28 = load i32, i32* %6, align 4
  %29 = icmp slt i32 %27, %28
  br i1 %29, label %30, label %35

30:                                               ; preds = %26
  %31 = load i8*, i8** %5, align 8
  %32 = load i8, i8* %31, align 1
  %33 = sext i8 %32 to i32
  %34 = icmp ne i32 %33, 0
  br label %35

35:                                               ; preds = %30, %26
  %36 = phi i1 [ false, %26 ], [ %34, %30 ]
  br i1 %36, label %37, label %61

37:                                               ; preds = %35
  %38 = load i8*, i8** %5, align 8
  %39 = getelementptr inbounds i8, i8* %38, i64 0
  %40 = load i8, i8* %39, align 1
  %41 = sext i8 %40 to i32
  %42 = icmp eq i32 %41, 37
  br i1 %42, label %43, label %58

43:                                               ; preds = %37
  %44 = load i8*, i8** %5, align 8
  %45 = getelementptr inbounds i8, i8* %44, i64 1
  %46 = load i8, i8* %45, align 1
  %47 = sext i8 %46 to i32
  %48 = icmp eq i32 %47, 37
  br i1 %48, label %49, label %58

49:                                               ; preds = %43
  %50 = load i8*, i8** %5, align 8
  %51 = getelementptr inbounds i8, i8* %50, i64 2
  %52 = load i8, i8* %51, align 1
  %53 = sext i8 %52 to i32
  %54 = icmp eq i32 %53, 10
  br i1 %54, label %55, label %58

55:                                               ; preds = %49
  %56 = load i32, i32* %7, align 4
  %57 = add nsw i32 %56, 1
  store i32 %57, i32* %7, align 4
  br label %58

58:                                               ; preds = %55, %49, %43, %37
  %59 = load i8*, i8** %5, align 8
  %60 = getelementptr inbounds i8, i8* %59, i32 1
  store i8* %60, i8** %5, align 8
  br label %26

61:                                               ; preds = %35
  %62 = load i8*, i8** %5, align 8
  %63 = load i8, i8* %62, align 1
  %64 = sext i8 %63 to i32
  %65 = icmp ne i32 %64, 0
  br i1 %65, label %66, label %69

66:                                               ; preds = %61
  %67 = load i8*, i8** %5, align 8
  %68 = getelementptr inbounds i8, i8* %67, i64 2
  store i8* %68, i8** %4, align 8
  br label %71

69:                                               ; preds = %61
  %70 = load i8*, i8** %5, align 8
  store i8* %70, i8** %4, align 8
  br label %71

71:                                               ; preds = %69, %66, %23
  %72 = load i8*, i8** %4, align 8
  ret i8* %72
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @parse_int_array(i8*, i32*, i32) #0 {
  %4 = atomicrmw add i64* @parse_int_array.glob, i64 1 seq_cst
  %5 = alloca i8*, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i8* %0, i8** %5, align 8
  store i32* %1, i32** %6, align 8
  store i32 %2, i32* %7, align 4
  store i32 0, i32* %10, align 4
  %12 = load i8*, i8** %5, align 8
  %13 = icmp ne i8* %12, null
  br i1 %13, label %14, label %15

14:                                               ; preds = %3
  br label %15

15:                                               ; preds = %14, %3
  %16 = phi i1 [ false, %3 ], [ true, %14 ]
  %17 = xor i1 %16, true
  %18 = zext i1 %17 to i32
  %19 = sext i32 %18 to i64
  %20 = icmp ne i64 %19, 0
  br i1 %20, label %21, label %23

21:                                               ; preds = %15
  call void @__assert_rtn(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @__func__.parse_int_array, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 55, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.12, i32 0, i32 0)) #4
  unreachable

22:                                               ; No predecessors!
  br label %24

23:                                               ; preds = %15
  br label %24

24:                                               ; preds = %23, %22
  %25 = load i8*, i8** %5, align 8
  %26 = call i8* @strtok(i8* %25, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.13, i32 0, i32 0))
  store i8* %26, i8** %8, align 8
  br label %27

27:                                               ; preds = %49, %24
  %28 = load i8*, i8** %8, align 8
  %29 = icmp ne i8* %28, null
  br i1 %29, label %30, label %34

30:                                               ; preds = %27
  %31 = load i32, i32* %10, align 4
  %32 = load i32, i32* %7, align 4
  %33 = icmp slt i32 %31, %32
  br label %34

34:                                               ; preds = %30, %27
  %35 = phi i1 [ false, %27 ], [ %33, %30 ]
  br i1 %35, label %36, label %62

36:                                               ; preds = %34
  %37 = load i8*, i8** %8, align 8
  store i8* %37, i8** %9, align 8
  %38 = load i8*, i8** %8, align 8
  %39 = call i64 @strtol(i8* %38, i8** %9, i32 10)
  %40 = trunc i64 %39 to i32
  store i32 %40, i32* %11, align 4
  %41 = load i8*, i8** %9, align 8
  %42 = load i8, i8* %41, align 1
  %43 = sext i8 %42 to i32
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %45, label %49

45:                                               ; preds = %36
  %46 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %47 = load i32, i32* %10, align 4
  %48 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %46, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.14, i32 0, i32 0), i32 %47)
  br label %49

49:                                               ; preds = %45, %36
  %50 = load i32, i32* %11, align 4
  %51 = load i32*, i32** %6, align 8
  %52 = load i32, i32* %10, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds i32, i32* %51, i64 %53
  store i32 %50, i32* %54, align 4
  %55 = load i32, i32* %10, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %10, align 4
  %57 = load i8*, i8** %8, align 8
  %58 = load i8*, i8** %8, align 8
  %59 = call i64 @strlen(i8* %58)
  %60 = getelementptr inbounds i8, i8* %57, i64 %59
  store i8 10, i8* %60, align 1
  %61 = call i8* @strtok(i8* null, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.13, i32 0, i32 0))
  store i8* %61, i8** %8, align 8
  br label %27

62:                                               ; preds = %34
  %63 = load i8*, i8** %8, align 8
  %64 = icmp ne i8* %63, null
  br i1 %64, label %65, label %70

65:                                               ; preds = %62
  %66 = load i8*, i8** %8, align 8
  %67 = load i8*, i8** %8, align 8
  %68 = call i64 @strlen(i8* %67)
  %69 = getelementptr inbounds i8, i8* %66, i64 %68
  store i8 10, i8* %69, align 1
  br label %70

70:                                               ; preds = %65, %62
  ret i32 0
}

declare i8* @strtok(i8*, i8*) #2

declare i64 @strtol(i8*, i8**, i32) #2

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #2

declare i64 @strlen(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @run_benchmark() #0 {
  %1 = atomicrmw add i64* @run_benchmark.glob, i64 1 seq_cst
  %2 = alloca %struct.bench_args_t, align 4
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.15, i32 0, i32 0), i8** %3, align 8
  %11 = load i8*, i8** %3, align 8
  %12 = call i32 (i8*, i32, ...) @"\01_open"(i8* %11, i32 0)
  store i32 %12, i32* %4, align 4
  %13 = load i32, i32* %4, align 4
  %14 = icmp sgt i32 %13, 0
  br i1 %14, label %15, label %16

15:                                               ; preds = %0
  br label %16

16:                                               ; preds = %15, %0
  %17 = phi i1 [ false, %0 ], [ true, %15 ]
  %18 = xor i1 %17, true
  %19 = zext i1 %18 to i32
  %20 = sext i32 %19 to i64
  %21 = icmp ne i64 %20, 0
  br i1 %21, label %22, label %24

22:                                               ; preds = %16
  call void @__assert_rtn(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @__func__.run_benchmark, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i32 0, i32 0), i32 83, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.17, i32 0, i32 0)) #4
  unreachable

23:                                               ; No predecessors!
  br label %25

24:                                               ; preds = %16
  br label %25

25:                                               ; preds = %24, %23
  %26 = load i32, i32* %4, align 4
  %27 = call i8* @readfile(i32 %26)
  store i8* %27, i8** %5, align 8
  %28 = load i8*, i8** %5, align 8
  %29 = call i8* @find_section_start(i8* %28, i32 1)
  store i8* %29, i8** %6, align 8
  %30 = load i8*, i8** %6, align 8
  %31 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 0
  %32 = getelementptr inbounds [4096 x i32], [4096 x i32]* %31, i32 0, i32 0
  %33 = call i32 @parse_int_array(i8* %30, i32* %32, i32 4096)
  %34 = load i8*, i8** %5, align 8
  %35 = call i8* @find_section_start(i8* %34, i32 2)
  store i8* %35, i8** %6, align 8
  %36 = load i8*, i8** %6, align 8
  %37 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 1
  %38 = getelementptr inbounds [4096 x i32], [4096 x i32]* %37, i32 0, i32 0
  %39 = call i32 @parse_int_array(i8* %36, i32* %38, i32 4096)
  %40 = load i8*, i8** %5, align 8
  call void @free(i8* %40)
  store i32 0, i32* %7, align 4
  br label %41

41:                                               ; preds = %60, %25
  %42 = load i32, i32* %7, align 4
  %43 = icmp slt i32 %42, 64
  br i1 %43, label %44, label %63

44:                                               ; preds = %41
  store i32 0, i32* %8, align 4
  br label %45

45:                                               ; preds = %56, %44
  %46 = load i32, i32* %8, align 4
  %47 = icmp slt i32 %46, 64
  br i1 %47, label %48, label %59

48:                                               ; preds = %45
  %49 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %50 = load i32, i32* %7, align 4
  %51 = mul nsw i32 %50, 64
  %52 = load i32, i32* %8, align 4
  %53 = add nsw i32 %51, %52
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds [4096 x i32], [4096 x i32]* %49, i64 0, i64 %54
  store i32 0, i32* %55, align 4
  br label %56

56:                                               ; preds = %48
  %57 = load i32, i32* %8, align 4
  %58 = add nsw i32 %57, 1
  store i32 %58, i32* %8, align 4
  br label %45

59:                                               ; preds = %45
  br label %60

60:                                               ; preds = %59
  %61 = load i32, i32* %7, align 4
  %62 = add nsw i32 %61, 1
  store i32 %62, i32* %7, align 4
  br label %41

63:                                               ; preds = %41
  %64 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 0
  %65 = getelementptr inbounds [4096 x i32], [4096 x i32]* %64, i32 0, i32 0
  %66 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 1
  %67 = getelementptr inbounds [4096 x i32], [4096 x i32]* %66, i32 0, i32 0
  %68 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %69 = getelementptr inbounds [4096 x i32], [4096 x i32]* %68, i32 0, i32 0
  call void @gemm(i32* %65, i32* %67, i32* %69)
  store i32 0, i32* %9, align 4
  br label %70

70:                                               ; preds = %82, %63
  %71 = load i32, i32* %9, align 4
  %72 = icmp slt i32 %71, 64
  br i1 %72, label %73, label %85

73:                                               ; preds = %70
  store i32 0, i32* %10, align 4
  br label %74

74:                                               ; preds = %78, %73
  %75 = load i32, i32* %10, align 4
  %76 = icmp slt i32 %75, 64
  br i1 %76, label %77, label %81

77:                                               ; preds = %74
  br label %78

78:                                               ; preds = %77
  %79 = load i32, i32* %10, align 4
  %80 = add nsw i32 %79, 1
  store i32 %80, i32* %10, align 4
  br label %74

81:                                               ; preds = %74
  br label %82

82:                                               ; preds = %81
  %83 = load i32, i32* %9, align 4
  %84 = add nsw i32 %83, 1
  store i32 %84, i32* %9, align 4
  br label %70

85:                                               ; preds = %70
  %86 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %87 = getelementptr inbounds [4096 x i32], [4096 x i32]* %86, i64 0, i64 4095
  %88 = load i32, i32* %87, align 4
  %89 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.18, i32 0, i32 0), i32 %88)
  ret void
}

declare i32 @"\01_open"(i8*, i32, ...) #2

declare void @free(i8*) #2

declare void @gemm(i32*, i32*, i32*) #2

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = atomicrmw add i64* @main.glob, i64 1 seq_cst
  %2 = alloca i32, align 4
  store i32 0, i32* %2, align 4
  call void @run_benchmark()
  %instructionCounter.val = load i64, i64* @instructionCounter
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @formatLong, i32 0, i32 0), i64 %instructionCounter.val)
  %basicBlockCounter.val = load i64, i64* @basicBlockCounter
  %printf1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @formatLong.1, i32 0, i32 0), i64 %basicBlockCounter.val)
  %addCounter.val = load i64, i64* @addCounter
  %printf2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.2, i32 0, i32 0), i64 %addCounter.val)
  %subCounter.val = load i64, i64* @subCounter
  %printf3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.3, i32 0, i32 0), i64 %subCounter.val)
  %mulCounter.val = load i64, i64* @mulCounter
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.4, i32 0, i32 0), i64 %mulCounter.val)
  %divCounter.val = load i64, i64* @divCounter
  %printf5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.5, i32 0, i32 0), i64 %divCounter.val)
  %remCounter.val = load i64, i64* @remCounter
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.6, i32 0, i32 0), i64 %remCounter.val)
  %andCounter.val = load i64, i64* @andCounter
  %printf7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.7, i32 0, i32 0), i64 %andCounter.val)
  %orCounter.val = load i64, i64* @orCounter
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @formatLong.8, i32 0, i32 0), i64 %orCounter.val)
  %xorCounter.val = load i64, i64* @xorCounter
  %printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.9, i32 0, i32 0), i64 %xorCounter.val)
  %branchCounter.val = load i64, i64* @branchCounter
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @formatLong.10, i32 0, i32 0), i64 %branchCounter.val)
  %switchCounter.val = load i64, i64* @switchCounter
  %printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @formatLong.11, i32 0, i32 0), i64 %switchCounter.val)
  %storeCounter.val = load i64, i64* @storeCounter
  %printf12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @formatLong.12, i32 0, i32 0), i64 %storeCounter.val)
  %loadCounter.val = load i64, i64* @loadCounter
  %printf13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @formatLong.13, i32 0, i32 0), i64 %loadCounter.val)
  %otherCount.val = load i64, i64* @otherCount
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @formatLong.14, i32 0, i32 0), i64 %otherCount.val)
  %printf15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @formatEmpty, i32 0, i32 0))
  %readfile.val = load i64, i64* @readfile.glob
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @formatLong.15, i32 0, i32 0), i64 %readfile.val)
  %__assert_rtn.val = load i64, i64* @__assert_rtn.glob
  %printf17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @formatLong.16, i32 0, i32 0), i64 %__assert_rtn.val)
  %"\01_fstat$INODE64.val" = load i64, i64* @"\01_fstat$INODE64.glob"
  %printf18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @formatLong.17, i32 0, i32 0), i64 %"\01_fstat$INODE64.val")
  %malloc.val = load i64, i64* @malloc.glob
  %printf19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.18, i32 0, i32 0), i64 %malloc.val)
  %"\01_read.val" = load i64, i64* @"\01_read.glob"
  %printf20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.19, i32 0, i32 0), i64 %"\01_read.val")
  %"\01_close.val" = load i64, i64* @"\01_close.glob"
  %printf21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @formatLong.20, i32 0, i32 0), i64 %"\01_close.val")
  %find_section_start.val = load i64, i64* @find_section_start.glob
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @formatLong.21, i32 0, i32 0), i64 %find_section_start.val)
  %parse_int_array.val = load i64, i64* @parse_int_array.glob
  %printf23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @formatLong.22, i32 0, i32 0), i64 %parse_int_array.val)
  %strtok.val = load i64, i64* @strtok.glob
  %printf24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.23, i32 0, i32 0), i64 %strtok.val)
  %strtol.val = load i64, i64* @strtol.glob
  %printf25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.24, i32 0, i32 0), i64 %strtol.val)
  %fprintf.val = load i64, i64* @fprintf.glob
  %printf26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @formatLong.25, i32 0, i32 0), i64 %fprintf.val)
  %strlen.val = load i64, i64* @strlen.glob
  %printf27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.26, i32 0, i32 0), i64 %strlen.val)
  %run_benchmark.val = load i64, i64* @run_benchmark.glob
  %printf28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @formatLong.27, i32 0, i32 0), i64 %run_benchmark.val)
  %"\01_open.val" = load i64, i64* @"\01_open.glob"
  %printf29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.28, i32 0, i32 0), i64 %"\01_open.val")
  %free.val = load i64, i64* @free.glob
  %printf30 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.29, i32 0, i32 0), i64 %free.val)
  %gemm.val = load i64, i64* @gemm.glob
  %printf31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.30, i32 0, i32 0), i64 %gemm.val)
  %printf.val = load i64, i64* @printf.glob
  %printf32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.31, i32 0, i32 0), i64 %printf.val)
  %main.val = load i64, i64* @main.glob
  %printf33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.32, i32 0, i32 0), i64 %main.val)
  ret i32 1
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="true" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { cold noreturn }
attributes #5 = { allocsize(0) }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"Apple clang version 11.0.0 (clang-1100.0.33.8)"}
