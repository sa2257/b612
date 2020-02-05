; ModuleID = 'gemm.c'
source_filename = "gemm.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

@gemm.glob = external global i64
@instructionCounter = external global i64
@basicBlockCounter = external global i64
@addCounter = external global i64
@subCounter = external global i64
@mulCounter = external global i64
@divCounter = external global i64
@remCounter = external global i64
@andCounter = external global i64
@orCounter = external global i64
@xorCounter = external global i64
@branchCounter = external global i64
@switchCounter = external global i64
@storeCounter = external global i64
@loadCounter = external global i64
@otherCount = external global i64

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @gemm(i32*, i32*, i32*) #0 {
  %4 = atomicrmw add i64* @gemm.glob, i64 1 seq_cst
  %5 = alloca i32*, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store i32* %0, i32** %5, align 8
  store i32* %1, i32** %6, align 8
  store i32* %2, i32** %7, align 8
  %15 = atomicrmw add i64* @instructionCounter, i64 15 seq_cst
  %16 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %17 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %18 = atomicrmw add i64* @storeCounter, i64 3 seq_cst
  br label %19

; <label>:19:                                     ; preds = %3
  store i32 0, i32* %8, align 4
  %20 = atomicrmw add i64* @instructionCounter, i64 2 seq_cst
  %21 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %22 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %23 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  br label %24

; <label>:24:                                     ; preds = %137, %19
  %25 = load i32, i32* %8, align 4
  %26 = icmp slt i32 %25, 64
  %27 = atomicrmw add i64* @instructionCounter, i64 3 seq_cst
  %28 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %29 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %30 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %31 = atomicrmw add i64* @otherCount, i64 1 seq_cst
  br i1 %26, label %32, label %146

; <label>:32:                                     ; preds = %24
  %33 = atomicrmw add i64* @instructionCounter, i64 1 seq_cst
  %34 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %35 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  br label %36

; <label>:36:                                     ; preds = %32
  store i32 0, i32* %9, align 4
  %37 = atomicrmw add i64* @instructionCounter, i64 2 seq_cst
  %38 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %39 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %40 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  br label %41

; <label>:41:                                     ; preds = %124, %36
  %42 = load i32, i32* %9, align 4
  %43 = icmp slt i32 %42, 64
  %44 = atomicrmw add i64* @instructionCounter, i64 3 seq_cst
  %45 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %46 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %47 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %48 = atomicrmw add i64* @otherCount, i64 1 seq_cst
  br i1 %43, label %49, label %133

; <label>:49:                                     ; preds = %41
  %50 = load i32, i32* %8, align 4
  %51 = mul nsw i32 %50, 64
  store i32 %51, i32* %12, align 4
  store i32 0, i32* %14, align 4
  %52 = atomicrmw add i64* @instructionCounter, i64 5 seq_cst
  %53 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %54 = atomicrmw add i64* @mulCounter, i64 1 seq_cst
  %55 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %56 = atomicrmw add i64* @storeCounter, i64 2 seq_cst
  %57 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %58

; <label>:58:                                     ; preds = %49
  store i32 0, i32* %10, align 4
  %59 = atomicrmw add i64* @instructionCounter, i64 2 seq_cst
  %60 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %61 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %62 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  br label %63

; <label>:63:                                     ; preds = %100, %58
  %64 = load i32, i32* %10, align 4
  %65 = icmp slt i32 %64, 64
  %66 = atomicrmw add i64* @instructionCounter, i64 3 seq_cst
  %67 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %68 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %69 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  %70 = atomicrmw add i64* @otherCount, i64 1 seq_cst
  br i1 %65, label %71, label %109

; <label>:71:                                     ; preds = %63
  %72 = load i32, i32* %10, align 4
  %73 = mul nsw i32 %72, 64
  store i32 %73, i32* %11, align 4
  %74 = load i32*, i32** %5, align 8
  %75 = load i32, i32* %12, align 4
  %76 = load i32, i32* %10, align 4
  %77 = add nsw i32 %75, %76
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds i32, i32* %74, i64 %78
  %80 = load i32, i32* %79, align 4
  %81 = load i32*, i32** %6, align 8
  %82 = load i32, i32* %11, align 4
  %83 = load i32, i32* %9, align 4
  %84 = add nsw i32 %82, %83
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds i32, i32* %81, i64 %85
  %87 = load i32, i32* %86, align 4
  %88 = mul nsw i32 %80, %87
  store i32 %88, i32* %13, align 4
  %89 = load i32, i32* %13, align 4
  %90 = load i32, i32* %14, align 4
  %91 = add nsw i32 %90, %89
  store i32 %91, i32* %14, align 4
  %92 = atomicrmw add i64* @instructionCounter, i64 24 seq_cst
  %93 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %94 = atomicrmw add i64* @addCounter, i64 3 seq_cst
  %95 = atomicrmw add i64* @mulCounter, i64 2 seq_cst
  %96 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %97 = atomicrmw add i64* @storeCounter, i64 3 seq_cst
  %98 = atomicrmw add i64* @loadCounter, i64 11 seq_cst
  %99 = atomicrmw add i64* @otherCount, i64 4 seq_cst
  br label %100

; <label>:100:                                   ; preds = %71
  %101 = load i32, i32* %10, align 4
  %102 = add nsw i32 %101, 1
  store i32 %102, i32* %10, align 4
  %103 = atomicrmw add i64* @instructionCounter, i64 4 seq_cst
  %104 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %105 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %106 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %107 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %108 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %63

; <label>:109:                                   ; preds = %63
  %110 = load i32, i32* %14, align 4
  %111 = load i32*, i32** %7, align 8
  %112 = load i32, i32* %12, align 4
  %113 = load i32, i32* %9, align 4
  %114 = add nsw i32 %112, %113
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds i32, i32* %111, i64 %115
  store i32 %110, i32* %116, align 4
  %117 = atomicrmw add i64* @instructionCounter, i64 9 seq_cst
  %118 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %119 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %120 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %121 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %122 = atomicrmw add i64* @loadCounter, i64 4 seq_cst
  %123 = atomicrmw add i64* @otherCount, i64 2 seq_cst
  br label %124

; <label>:124:                                   ; preds = %109
  %125 = load i32, i32* %9, align 4
  %126 = add nsw i32 %125, 1
  store i32 %126, i32* %9, align 4
  %127 = atomicrmw add i64* @instructionCounter, i64 4 seq_cst
  %128 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %129 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %130 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %131 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %132 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %41

; <label>:133:                                   ; preds = %41
  %134 = atomicrmw add i64* @instructionCounter, i64 1 seq_cst
  %135 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %136 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  br label %137

; <label>:137:                                   ; preds = %133
  %138 = load i32, i32* %8, align 4
  %139 = add nsw i32 %138, 1
  store i32 %139, i32* %8, align 4
  %140 = atomicrmw add i64* @instructionCounter, i64 4 seq_cst
  %141 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  %142 = atomicrmw add i64* @addCounter, i64 1 seq_cst
  %143 = atomicrmw add i64* @branchCounter, i64 1 seq_cst
  %144 = atomicrmw add i64* @storeCounter, i64 1 seq_cst
  %145 = atomicrmw add i64* @loadCounter, i64 1 seq_cst
  br label %24

; <label>:146:                                   ; preds = %24
  %147 = atomicrmw add i64* @instructionCounter, i64 1 seq_cst
  %148 = atomicrmw add i64* @basicBlockCounter, i64 1 seq_cst
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "darwin-stkchk-strong-link" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"Apple clang version 11.0.0 (clang-1100.0.33.8)"}
