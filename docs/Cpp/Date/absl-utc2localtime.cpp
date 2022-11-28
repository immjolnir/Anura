
// UTC to Local Time
void utc2local() {
   absl::TimeZone lax;

   if (!absl::LoadTimeZone("America/Los_Angeles", &lax)) {
     // Handle failure
   }

  absl::Time t = absl::FromUnixSeconds(1234567890);
  absl::CivilSecond local_time = absl::ToCivilSecond(t, lax);

  // local_time has year, month, day, hour, minute, second
  // 2009-02-13 15:31:30 -0800 is Unix Time 1234567890

}

// Local Time to UTC
void local2utc() {
  absl::TimeZone lax; // absl::LoadTimeZone() as before

  CivilSecond local_time(2022, 10, 24, 12, 34, 56);

  absl::Time t = absl::FromCivil(local_time, lax);
  // t is '2022-10-24 19:34:56Z'
  // absl::ToUnixSeconds(t) == 1
  // What about skip and repeat?
}

void local2another() {
  absl::TimeZone lax, nyc; 
  CivilSecond lax_time(2022, 10, 24, 11, 30, 0);

  // 转换为绝对时间
  absl::Time t = absl::FromCivil(local_time, lax);
  t += abls::Hours(5) + absl::Minutes(30);

  absl::CivilSecond nyc_time = absl::ToCivilSecond(t, nyc);

}

int main(){
}
