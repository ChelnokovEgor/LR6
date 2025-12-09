package main

import (
	"container/list"
	"fmt"
	"sort"
)

const MAX_POS = 10001
const MAX_V = 10001
const INF = 1<<31 - 1

type State struct {
	pos, v, steps int
}

func path() {
	var K int
	fmt.Scanln(&K)
	targets := make([]int, K)
	for i := 0; i < K; i++ {
		fmt.Scanln(&targets[i])
	}
	sort.Ints(targets)

	dist := make([][]int, MAX_POS+1)
	from_pos := make([][]int, MAX_POS+1)
	from_v := make([][]int, MAX_POS+1)
	for i := 0; i <= MAX_POS; i++ {
		dist[i] = make([]int, MAX_V+1)
		from_pos[i] = make([]int, MAX_V+1)
		from_v[i] = make([]int, MAX_V+1)
		for j := 0; j <= MAX_V; j++ {
			dist[i][j] = INF
			from_pos[i][j] = -1
			from_v[i][j] = -1
		}
	}

	q := list.New()
	dist[1][0] = 0
	q.PushBack(State{pos: 1, v: 0, steps: 0})

	final_pos, final_v := -1, -1

	for q.Len() > 0 {
		elem := q.Front()
		q.Remove(elem)
		cur := elem.Value.(State)
		pos, v, steps := cur.pos, cur.v, cur.steps

		if dist[pos][v] != steps {
			continue
		}

		idx := sort.SearchInts(targets, pos+1)
		if idx == K {
			final_pos, final_v = pos, v
			break
		}
		next_target := targets[idx]

		for dv := -1; dv <= 1; dv++ {
			v_new := v + dv
			if v_new < 1 || v_new > MAX_V {
				continue
			}
			next_pos := pos + v_new
			if next_pos > MAX_POS || next_pos > next_target {
				continue
			}
			if dist[next_pos][v_new] > steps+1 {
				dist[next_pos][v_new] = steps + 1
				from_pos[next_pos][v_new] = pos
				from_v[next_pos][v_new] = v
				q.PushBack(State{pos: next_pos, v: v_new, steps: steps + 1})
			}
		}
	}

	moves := []struct{ speed, pos int }{}
	pos, v := final_pos, final_v
	for pos != 1 || v != 0 {
		prev_pos := from_pos[pos][v]
		prev_v := from_v[pos][v]
		moves = append(moves, struct{ speed, pos int }{speed: v, pos: pos})
		pos, v = prev_pos, prev_v
	}

	// reverse
	for i, j := 0, len(moves)-1; i < j; i, j = i+1, j-1 {
		moves[i], moves[j] = moves[j], moves[i]
	}

	for i, move := range moves {
		fmt.Printf("ход %d скорость %d позиция %d\n", i+1, move.speed, move.pos)
	}

	fmt.Println(len(moves))
}
