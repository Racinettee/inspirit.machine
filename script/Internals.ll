; ModuleID = 'Internals.cpp'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class.inspirit::IGameScreen" = type { i32 (...)**, i8 }
%"class.std::shared_ptr" = type { %"class.std::__shared_ptr" }
%"class.std::__shared_ptr" = type { %"class.inspirit::IGameScreen"*, %"class.std::__shared_count" }
%"class.std::__shared_count" = type { %"class.std::_Sp_counted_base"* }
%"class.std::_Sp_counted_base" = type { i32 (...)**, i32, i32 }

; Function Attrs: nounwind uwtable
define void @_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE(%"class.inspirit::IGameScreen"*) #0 align 2 {
  %2 = alloca %"class.inspirit::IGameScreen"*, align 8
  store %"class.inspirit::IGameScreen"* %0, %"class.inspirit::IGameScreen"** %2, align 8
  ret void
}

; Function Attrs: nounwind uwtable
define void @_ZN8inspirit6Engine9PopScreenEv(%"class.std::shared_ptr"* noalias sret %agg.result) #0 align 2 {
  call void @llvm.trap()
  unreachable
                                                  ; No predecessors!
  ret void
}

; Function Attrs: noreturn nounwind
declare void @llvm.trap() #1

; Function Attrs: nounwind uwtable
define %"class.inspirit::IGameScreen"* @_ZN8inspirit6Engine13CurrentScreenEv() #0 align 2 {
  %1 = alloca %"class.inspirit::IGameScreen"*, align 8
  call void @llvm.trap()
  unreachable
                                                  ; No predecessors!
  %3 = load %"class.inspirit::IGameScreen"** %1
  ret %"class.inspirit::IGameScreen"* %3
}

; Function Attrs: nounwind uwtable
define %"class.inspirit::IGameScreen"* @_ZN8inspirit6Engine9TopScreenEv() #0 align 2 {
  %1 = alloca %"class.inspirit::IGameScreen"*, align 8
  call void @llvm.trap()
  unreachable
                                                  ; No predecessors!
  %3 = load %"class.inspirit::IGameScreen"** %1
  ret %"class.inspirit::IGameScreen"* %3
}

; Function Attrs: nounwind uwtable
define double @_ZN8inspirit6Engine6DeltaTEv() #0 align 2 {
  %1 = alloca double, align 8
  call void @llvm.trap()
  unreachable
                                                  ; No predecessors!
  %3 = load double* %1
  ret double %3
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"}
