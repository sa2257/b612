; ModuleID = 'bench.ll'
source_filename = "bench.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.bench_args_t = type { [4096 x i32], [4096 x i32], [4096 x i32] }

@.str = private unnamed_addr constant [27 x i8] c"One example output is %d \0A\00", align 1
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
@run_benchmark.glob = common global i64 0
@rand.glob = common global i64 0
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
@formatLong.15 = private unnamed_addr constant [20 x i8] c"run_benchmark: %ld\0A\00", align 1
@formatLong.16 = private unnamed_addr constant [11 x i8] c"rand: %ld\0A\00", align 1
@formatLong.17 = private unnamed_addr constant [11 x i8] c"gemm: %ld\0A\00", align 1
@formatLong.18 = private unnamed_addr constant [13 x i8] c"printf: %ld\0A\00", align 1
@formatLong.19 = private unnamed_addr constant [11 x i8] c"main: %ld\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @run_benchmark() #0 {
  %1 = atomicrmw add i64* @run_benchmark.glob, i64 1 seq_cst
  %2 = alloca %struct.bench_args_t, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  %5 = atomicrmw add i64* @instructionCounter, i64 6 seq_cst
  %6 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %7 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %8 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  br label %9

; <label>:9:                                      ; preds = %81, %0
  %10 = load i32, i32* %3, align 4
  %11 = icmp slt i32 %10, 64
  %12 = atomicrmw add i64* @instructionCounter, i64 3 seq_cst
  %13 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %14 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %15 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %16 = atomicrmw add i64* @otherCount, i64 1 seq_cst
  br i1 %11, label %17, label %90

; <label>:17:                                     ; preds = %9
  store i32 0, i32* %4, align 4
  %18 = atomicrmw add i64* @instructionCounter, i64 2 seq_cst
  %19 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %20 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %21 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  br label %22

; <label>:22:                                     ; preds = %68, %17
  %23 = load i32, i32* %4, align 4
  %24 = icmp slt i32 %23, 64
  %25 = atomicrmw add i64* @instructionCounter, i64 3 seq_cst
  %26 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %27 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %28 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %29 = atomicrmw add i64* @otherCount, i64 1 seq_cst
  br i1 %24, label %30, label %77

; <label>:30:                                     ; preds = %22
  %31 = load i32, i32* %3, align 4
  %32 = mul nsw i32 %31, 64
  %33 = add nsw i32 1, %32
  %34 = load i32, i32* %4, align 4
  %35 = add nsw i32 %33, %34
  %36 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 0
  %37 = load i32, i32* %3, align 4
  %38 = mul nsw i32 %37, 64
  %39 = load i32, i32* %4, align 4
  %40 = add nsw i32 %38, %39
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds [4096 x i32], [4096 x i32]* %36, i64 0, i64 %41
  store i32 %35, i32* %42, align 4
  %43 = call i32 @rand()
  %44 = sdiv i32 %43, 4096
  %45 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 1
  %46 = load i32, i32* %3, align 4
  %47 = mul nsw i32 %46, 64
  %48 = load i32, i32* %4, align 4
  %49 = add nsw i32 %47, %48
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds [4096 x i32], [4096 x i32]* %45, i64 0, i64 %50
  store i32 %44, i32* %51, align 4
  %52 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %53 = load i32, i32* %3, align 4
  %54 = mul nsw i32 %53, 64
  %55 = load i32, i32* %4, align 4
  %56 = add nsw i32 %54, %55
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds [4096 x i32], [4096 x i32]* %52, i64 0, i64 %57
  store i32 0, i32* %58, align 4
  %59 = atomicrmw add i64* @instructionCounter, i64 32 seq_cst
  %60 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %61 = atomicrmw add i64* @addCounter, i64 5 seq_cst
  %62 = atomicrmw add i64* @mulCounter, i64 4 seq_cst
  %63 = atomicrmw add i64* @divCounter, i64 1 seq_cst
  %64 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %65 = atomicrmw add i64* @storeCounter, i64 3 seq_cst
  %66 = atomicrmw add i64* @loadCounter, i64 8 seq_cst
  %67 = atomicrmw add i64* @otherCount, i64 9 seq_cst
  br label %68

; <label>:68:                                    ; preds = %30
  %69 = load i32, i32* %4, align 4
  %70 = add nsw i32 %69, 1
  store i32 %70, i32* %4, align 4
  %71 = atomicrmw add i64* @instructionCounter, i64 4 seq_cst
  %72 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %73 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %74 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %75 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %76 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %22

; <label>:77:                                    ; preds = %22
  %78 = atomicrmw add i64* @instructionCounter, i64 1 seq_cst
  %79 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %80 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  br label %81

; <label>:81:                                    ; preds = %77
  %82 = load i32, i32* %3, align 4
  %83 = add nsw i32 %82, 1
  store i32 %83, i32* %3, align 4
  %84 = atomicrmw add i64* @instructionCounter, i64 4 seq_cst
  %85 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %86 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %87 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %88 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %89 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %9

; <label>:90:                                    ; preds = %9
  %91 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 0
  %92 = getelementptr inbounds [4096 x i32], [4096 x i32]* %91, i32 0, i32 0
  %93 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 1
  %94 = getelementptr inbounds [4096 x i32], [4096 x i32]* %93, i32 0, i32 0
  %95 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %96 = getelementptr inbounds [4096 x i32], [4096 x i32]* %95, i32 0, i32 0
  call void @gemm(i32* %92, i32* %94, i32* %96)
  %97 = getelementptr inbounds %struct.bench_args_t, %struct.bench_args_t* %2, i32 0, i32 2
  %98 = getelementptr inbounds [4096 x i32], [4096 x i32]* %97, i64 0, i64 4095
  %99 = load i32, i32* %98, align 4
  %100 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str, i32 0, i32 0), i32 %99)
  %101 = atomicrmw add i64* @instructionCounter, i64 12 seq_cst
  %102 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %103 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %104 = atomicrmw add i64* @otherCount, i64 8 seq_cst
  ret void
}

declare i32 @rand() #1

declare void @gemm(i32*, i32*, i32*) #1

declare i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = atomicrmw add i64* @main.glob, i64 1 seq_cst
  %2 = alloca i32, align 4
  store i32 0, i32* %2, align 4
  call void @run_benchmark()
  %3 = atomicrmw add i64* @instructionCounter, i64 5 seq_cst
  %4 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %5 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
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
  %run_benchmark.val = load i64, i64* @run_benchmark.glob
  %printf15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @formatLong.15, i32 0, i32 0), i64 %run_benchmark.val)
  %rand.val = load i64, i64* @rand.glob
  %printf16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.16, i32 0, i32 0), i64 %rand.val)
  %gemm.val = load i64, i64* @gemm.glob
  %printf17 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.17, i32 0, i32 0), i64 %gemm.val)
  %printf.val = load i64, i64* @printf.glob
  %printf18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @formatLong.18, i32 0, i32 0), i64 %printf.val)
  %main.val = load i64, i64* @main.glob
  %printf19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @formatLong.19, i32 0, i32 0), i64 %main.val)
  ret i32 1
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"Apple clang version 11.0.0 (clang-1100.0.33.8)"}
