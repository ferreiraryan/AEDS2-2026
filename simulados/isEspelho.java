

boolean isEspelho(No a, No b){
  if(a == null & b ==null) return true;
  if(a== null || b == null) return false;
  return a.elemento == b.elemento && isEspelho(a.esq,b.dir) && isEspelho(a.dir,b.esq);
}

