/* Fleet policy (SPEC.md 6.1): disable LeakSanitizer preventively at BUILD time. ASan
   use-after-free/overflow and UBSan stay fully on and halting -- only leak detection is affected.

   the harness drives GEOS' WKT/WKB geometry readers over attacker-controlled input. A
   geometry rejected mid-parse leaves partially-built GEOSGeometry nodes owned by the caller, so
   LSan reports on inputs that are not the defect being hunted.

   A runtime ASan default-options override -- whether compiled in or passed via ASAN_OPTIONS -- is
   forbidden, because Mayhem alone owns the runtime ASAN/LibFuzzer option set, so this is done via
   the sanctioned build-time hook instead. SPEC.md 6.2 item 15 bans the override symbol NAMES
   anywhere under mayhem/, comments included, so the forbidden construct is described in prose here
   rather than named. __lsan_is_turned_off is the sanctioned hook and is NOT the banned construct. */
int __lsan_is_turned_off(void) {
  return 1;
}
